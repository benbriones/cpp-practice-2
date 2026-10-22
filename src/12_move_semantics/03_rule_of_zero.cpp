// === Lesson: The rule of zero ================================================
//
// The compiler-generated destructor, copies and moves work member by member:
// copying the class copies each member, moving it moves each member, and
// destroying it destroys each member. When every member already manages itself
// (std::string, std::vector, std::map, std::unique_ptr, plain values), that's
// exactly right, and you write none of the five. That's the rule of zero:
//
//     class Contact {
//     public:
//         Contact(std::string name, std::vector<std::string> phones)
//             : name_(std::move(name)), phones_(std::move(phones)) {}
//
//     private:
//         std::string name_;
//         std::vector<std::string> phones_;
//     };   // no destructor, no copy or move operations written by hand
//
//     Contact a("Ada", {"555-0100"});
//     Contact b = a;               // copies both members
//     Contact c = std::move(a);    // moves both members; noexcept, for free
//
// Hand-written special members are where memory bugs live. Typical ones:
// copying a pointer member instead of what it points to, forgetting a member in
// operator=, breaking on self-assignment, and leaking when an allocation throws
// halfway through. The compiler catches none of them.
//
// So the rule of three and five are for the rare class whose whole job is
// managing one resource. Everything else uses those classes as members and
// follows the rule of zero.
//
// Writing the declarations yourself isn't neutral:
// - `T(const T &) = delete;` forbids copying (and, as a declared copy
//   operation, still turns off the implicit moves).
// - `~T() = default;` keeps the default behavior but also turns off the
//   implicit moves.
// - Writing nothing gets you all five, correct and with moves noexcept
//   whenever the members' moves are.
//
// You can prove the moves are there and can't throw:
//
//     static_assert(std::is_nothrow_move_constructible_v<Contact>);
//
// Read more: https://en.cppreference.com/w/cpp/language/rule_of_three
//
// === Exercise: The rule of zero ==============================================
// This Playlist manages memory by hand: new[], delete[], a destructor, a copy
// constructor, and copy assignment. That code has bugs, and the class has no
// move operations at all.
//
// Rewrite the private part using std::string and std::vector<std::string>, then
// remove the destructor, copy constructor, and copy assignment from the class
// (remove them, don't `= delete` them). Keep the public functions working the
// same way.
//
// ./grade 12_move_semantics/03_rule_of_zero

#include <cstddef>
#include <stdexcept>
#include <string>

class Playlist {
public:
    explicit Playlist(const std::string &name)
        : name_(new char[name.size() + 1]), songs_(new std::string[2]), count_(0), capacity_(2) {
        for (std::size_t i = 0; i <= name.size(); ++i) name_[i] = name.c_str()[i];
    }

    ~Playlist() {
        delete[] name_;
        delete[] songs_;
    }

    Playlist(const Playlist &other)
        : name_(other.name_),
          songs_(new std::string[static_cast<std::size_t>(other.capacity_)]),
          count_(other.count_),
          capacity_(other.capacity_) {
        for (int i = 0; i < count_; ++i) songs_[i] = other.songs_[i];
    }

    Playlist &operator=(const Playlist &other) {
        delete[] songs_;
        songs_ = new std::string[static_cast<std::size_t>(other.capacity_)];
        for (int i = 0; i < other.count_; ++i) songs_[i] = other.songs_[i];
        count_ = other.count_;
        capacity_ = other.capacity_;
        return *this;
    }

    // Add song to the end of the playlist.
    // There's no size limit: the playlist grows as needed.
    //
    // Example:
    //   Playlist p("Road trip");
    //   p.add("Song A");
    //   p.add("Song B");
    //   // p.size() is 2, p.song(1) is "Song B".
    void add(const std::string &song) {
        if (count_ == capacity_) {
            capacity_ *= 2;
            std::string *bigger = new std::string[static_cast<std::size_t>(capacity_)];
            for (int i = 0; i < count_; ++i) bigger[i] = songs_[i];
            delete[] songs_;
            songs_ = bigger;
        }
        songs_[count_] = song;
        ++count_;
    }

    std::string name() const { return name_; }
    int size() const { return count_; }

    // Return the song at index, counting from 0.
    // Throw std::out_of_range for a bad index: negative, or size() or more.
    //
    // Example:
    //   songs are "Song A", "Song B", "Song C"
    //   p.song(0) is "Song A", p.song(2) is "Song C"
    //   p.song(3) and p.song(-1) throw std::out_of_range
    const std::string &song(int index) const {
        if (index < 0 || index >= count_) throw std::out_of_range("no song at that index");
        return songs_[index];
    }

private:
    char *name_;
    std::string *songs_;
    int count_;
    int capacity_;
};
