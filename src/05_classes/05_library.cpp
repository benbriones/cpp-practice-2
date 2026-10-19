// === Lesson: Designing a class ===============================================
//
// When the public interface is fixed, the design work is choosing the private
// data. Start from the operations: for each public function, ask what it needs
// to look up or change, and pick members that make those steps simple.
//
// Keep each fact in one place. If the same fact is stored twice (say, a count
// kept next to the list it counts), every change has to update both, and one
// missed update leaves them disagreeing. When a value is cheap to compute from
// the data, compute it instead of storing it.
//
// Say "maybe" with a type. std::optional<T> (module 03) holds a T or nothing,
// which reads better and breaks less than a magic value like "" or -1.
//
// Order is a design choice too. A std::vector keeps elements in the order you
// added them; std::map and std::set (module 06) keep them sorted instead.
//
// Small private helpers keep the public functions short. A lookup helper that
// returns a pointer, or nullptr when nothing matches, lets callers both test
// the result and change it:
//
//     class Phonebook {
//     public:
//         bool change_number(const std::string& name, const std::string& number) {
//             Entry* entry = find(name);
//             if (entry == nullptr) return false;
//             entry->number = number;
//             return true;
//         }
//
//     private:
//         struct Entry {   // a type only this class uses can live inside it
//             std::string name;
//             std::string number;
//         };
//
//         Entry* find(const std::string& name) {
//             for (Entry& e : entries_) {
//                 if (e.name == name) return &e;
//             }
//             return nullptr;
//         }
//         // A const twin, so const member functions can search as well.
//         const Entry* find(const std::string& name) const { ... same loop ... }
//
//         std::vector<Entry> entries_;
//     };
//
// A pointer from find() is only good until entries_ changes size: push_back can
// move every element to a new block of memory.
//
// Class-wide constants: static constexpr int kMaxLength = 20; inside the class
// is one value shared by every object, written Phonebook::kMaxLength outside it.
//
// Read more: https://www.learncpp.com/cpp-tutorial/nested-types-member-types/
//            https://www.learncpp.com/cpp-tutorial/static-member-variables/
//
// === Challenge: Library ======================================================
// Build a small lending library. The public interface below is fixed (the tests use it);
// the private data members, any struct you need, and helper functions are your design.
//
// Rules: titles are unique. A book is either on the shelf or lent to one member, and a
// member can hold at most kMaxLoans books at once.
//
// ./grade 05_classes/05_library

#include <string>
#include <vector>

class Library {
public:
    static constexpr int kMaxLoans = 3;

    // Add a book to the shelf. Return false (and change nothing) if the title already exists.
    bool add_book(const std::string& title, const std::string& author) {
        throw "TODO";
    }

    // Lend a book to `member`. Return false if the title is unknown, the book is already
    // lent out, or the member already holds kMaxLoans books.
    bool checkout(const std::string& title, const std::string& member) {
        throw "TODO";
    }

    // Put a lent book back on the shelf. Return false if the title is unknown or not lent out.
    bool return_book(const std::string& title) {
        throw "TODO";
    }

    // True if the book exists and is on the shelf.
    bool is_available(const std::string& title) const {
        throw "TODO";
    }

    // Titles by `author`, in the order they were added.
    std::vector<std::string> books_by(const std::string& author) const {
        throw "TODO";
    }

    // Titles currently lent to `member`, in the order the books were added to the library.
    std::vector<std::string> loans_of(const std::string& member) const {
        throw "TODO";
    }

    // Books on the shelf right now.
    int available_count() const {
        throw "TODO";
    }

    // All books, lent or not.
    int size() const {
        throw "TODO";
    }

private:
    // TODO: your data members
};
