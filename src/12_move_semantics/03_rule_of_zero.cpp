// Exercise: The rule of zero
// This Playlist manages memory by hand: new[], delete[], a destructor, a copy
// constructor, and copy assignment. That code has bugs, and the class has no
// move operations at all.
//
// Rewrite the private part using std::string and std::vector<std::string>, then
// remove the destructor, copy constructor, and copy assignment from the class
// (remove them, don't `= delete` them).
// With members that manage themselves, the compiler-generated copies, moves, and
// destructor are all correct: that's the rule of zero. Keep the public functions
// working the same way.
//
// Grade: grade 12_move_semantics/03_rule_of_zero

#include <cstddef>
#include <stdexcept>
#include <string>

class Playlist {
public:
    explicit Playlist(const std::string& name)
        : name_(new char[name.size() + 1]), songs_(new std::string[2]), count_(0), capacity_(2) {
        for (std::size_t i = 0; i <= name.size(); ++i) name_[i] = name.c_str()[i];
    }

    ~Playlist() {
        delete[] name_;
        delete[] songs_;
    }

    Playlist(const Playlist& other)
        : name_(other.name_),
          songs_(new std::string[static_cast<std::size_t>(other.capacity_)]),
          count_(other.count_),
          capacity_(other.capacity_) {
        for (int i = 0; i < count_; ++i) songs_[i] = other.songs_[i];
    }

    Playlist& operator=(const Playlist& other) {
        delete[] songs_;
        songs_ = new std::string[static_cast<std::size_t>(other.capacity_)];
        for (int i = 0; i < other.count_; ++i) songs_[i] = other.songs_[i];
        count_ = other.count_;
        capacity_ = other.capacity_;
        return *this;
    }

    // Append a song.
    void add(const std::string& song) {
        if (count_ == capacity_) {
            capacity_ *= 2;
            std::string* bigger = new std::string[static_cast<std::size_t>(capacity_)];
            for (int i = 0; i < count_; ++i) bigger[i] = songs_[i];
            delete[] songs_;
            songs_ = bigger;
        }
        songs_[count_] = song;
        ++count_;
    }

    std::string name() const { return name_; }
    int size() const { return count_; }

    // The song at index; throws std::out_of_range for a bad index.
    const std::string& song(int index) const {
        if (index < 0 || index >= count_) throw std::out_of_range("no song at that index");
        return songs_[index];
    }

private:
    char* name_;
    std::string* songs_;
    int count_;
    int capacity_;
};
