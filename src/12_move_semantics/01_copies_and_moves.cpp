// Exercise: Copies and moves
// Copying duplicates an object's contents; moving steals them and leaves the
// source empty but still usable. The compiler calls the move versions for
// rvalues: temporaries, and anything wrapped in std::move(...).
//
//   Message(Message&& other) noexcept;              // move constructor
//   Message& operator=(Message&& other) noexcept;   // move assignment
//
// Write the four copy/move operations, counting each one in the globals below,
// then the three functions underneath. Mark the two move operations noexcept
// once you've implemented them (std::vector relies on it).
//
// ./grade 12_move_semantics/01_copies_and_moves

#include <string>
#include <utility>
#include <vector>

// The tests read these to see exactly which operations ran.
inline int copies = 0;
inline int moves = 0;

class Message {
public:
    explicit Message(std::string text) : text_(std::move(text)) {}

    // Copy other's text; count one copy.
    Message(const Message& other) {
        throw "TODO";
    }

    // Take other's text with std::move; count one move. Leave other's text empty
    // (std::string's move usually does, but other.text_.clear() guarantees it).
    Message(Message&& other) {
        throw "TODO";
    }

    // Copy other's text into this message; count one copy; return *this.
    Message& operator=(const Message& other) {
        throw "TODO";
    }

    // Take other's text; count one move; leave other's text empty; return *this.
    Message& operator=(Message&& other) {
        throw "TODO";
    }

    const std::string& text() const { return text_; }

private:
    std::string text_;
};

// A "sink": take message by value, then move it into the box. A caller passing
// a temporary or std::move(x) then pays for no copies at all.
void store(std::vector<Message>& box, Message message) {
    throw "TODO";
}

// Return a new Message holding text. No copies or moves should happen: return
// a local by name (or a temporary) and the compiler builds it in place.
// `return std::move(local);` actually costs you a move.
Message make_message(const std::string& text) {
    throw "TODO";
}

// n messages "message 1" ... "message n", built directly inside the vector so
// no Message is ever copied or moved: reserve() first, then emplace_back().
std::vector<Message> make_batch(int n) {
    throw "TODO";
}
