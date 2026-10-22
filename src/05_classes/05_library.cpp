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
//         bool change_number(const std::string &name, const std::string &number) {
//             Entry *entry = find(name);
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
//         Entry *find(const std::string &name) {
//             for (Entry &e : entries_) {
//                 if (e.name == name) return &e;
//             }
//             return nullptr;
//         }
//         // A const twin, so const member functions can search as well.
//         const Entry *find(const std::string &name) const { ... same loop ... }
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

    // Add a book to the shelf and return true.
    // Titles are unique: if the title already exists, return false and change nothing,
    // even when the author is different.
    //
    // Example:
    //   library.add_book("Dune", "Herbert");        // true; size() is 1
    //   library.add_book("Dune", "Someone Else");   // false; size() is still 1
    bool add_book(const std::string &title, const std::string &author) {
        throw "TODO";
    }

    // Lend a book to `member` and return true.
    // Return false if the title is unknown, the book is already lent out, or the member
    // already holds kMaxLoans books. A failed checkout changes nothing.
    //
    // Example (the library holds Dune, Emma, Persuasion and Neuromancer):
    //   library.checkout("Emma", "ada");          // true: Emma is now lent to ada
    //   library.checkout("Emma", "grace");        // false: Emma is already lent out
    //   library.checkout("Ulysses", "ada");       // false: no such title
    //   library.checkout("Dune", "ada");          // true
    //   library.checkout("Persuasion", "ada");    // true: ada now holds 3 books
    //   library.checkout("Neuromancer", "ada");   // false: ada already holds kMaxLoans
    bool checkout(const std::string &title, const std::string &member) {
        throw "TODO";
    }

    // Put a lent book back on the shelf and return true.
    // Return false if the title is unknown or the book isn't lent out.
    //
    // Example:
    //   library.checkout("Dune", "ada");
    //   library.return_book("Dune");      // true; Dune is available again
    //   library.return_book("Dune");      // false: it's already on the shelf
    //   library.return_book("Ulysses");   // false: no such title
    //
    // Returning a book frees one of the member's kMaxLoans slots.
    bool return_book(const std::string &title) {
        throw "TODO";
    }

    // Return true if the book exists and is on the shelf.
    // Unknown titles and lent-out books are not available.
    //
    // Example:
    //   library.add_book("Dune", "Herbert");
    //   library.is_available("Dune") is true
    //   library.is_available("Ulysses") is false   // no such title
    bool is_available(const std::string &title) const {
        throw "TODO";
    }

    // Return the titles by `author`, in the order they were added.
    // Books that are lent out still count. An unknown author gives {}.
    //
    // Example (Dune by Herbert, then Emma and Persuasion by Austen):
    //   library.books_by("Austen") is {"Emma", "Persuasion"}
    //   library.books_by("Nobody") is {}
    std::vector<std::string> books_by(const std::string &author) const {
        throw "TODO";
    }

    // Return the titles currently lent to `member`, in the order the books were added to
    // the library (not the order they were checked out).
    // A member with no loans gives {}.
    //
    // Example (books added in the order Dune, Emma, Persuasion, Neuromancer):
    //   library.checkout("Neuromancer", "ada");
    //   library.checkout("Dune", "ada");
    //   library.checkout("Emma", "grace");
    //   library.loans_of("ada") is {"Dune", "Neuromancer"}
    //   library.loans_of("grace") is {"Emma"}
    std::vector<std::string> loans_of(const std::string &member) const {
        throw "TODO";
    }

    // Return how many books are on the shelf right now. Lent-out books don't count.
    //
    // Example:
    //   4 books with Dune lent out: available_count() is 3
    int available_count() const {
        throw "TODO";
    }

    // Return how many books the library has, lent or not.
    //
    // Example:
    //   4 books with Dune lent out: size() is 4
    int size() const {
        throw "TODO";
    }

private:
    // TODO: your data members
};
