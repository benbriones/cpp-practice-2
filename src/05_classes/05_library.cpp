// Challenge: Library
// Build a small lending library. The public interface below is fixed (the tests use it);
// the private data members, any struct you need, and helper functions are your design.
//
// Rules: titles are unique. A book is either on the shelf or lent to one member, and a
// member can hold at most kMaxLoans books at once.
//
// Grade: grade 05_classes/05_library

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
