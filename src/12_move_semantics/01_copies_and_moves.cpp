// === Lesson: Copies, moves and rvalues =======================================
//
// Copying a std::string or std::vector duplicates its heap buffer. When the
// source is about to be thrown away anyway, that work is wasted: the new object
// could just take the buffer. That's a move. It leaves the source valid but
// "unspecified" (in practice, usually empty): you can destroy it or assign it a
// new value, but don't rely on what it holds.
//
// The compiler moves when the source is an rvalue: a temporary with no name,
// like the result of name + "!". Anything with a name is an lvalue. A parameter
// of type T&& (an "rvalue reference") binds only to rvalues, so overloading on
// const T& and T&& lets one function tell the two apart:
//
//     void take(const std::string& s);   // binds to anything
//     void take(std::string&& s);        // binds only to rvalues, and wins for them
//
//     std::string name = "Ada";
//     take(name);                 // name is an lvalue: the const& version
//     take(name + "!");           // a temporary: the && version
//     take(std::move(name));      // the && version: std::move is just a cast
//
// std::move doesn't move anything. It's a cast that says "treat this as an
// rvalue; I'm done with it". Whatever receives it does the moving. And inside
// take(std::string&& s), s has a name, so it's an lvalue again: to pass the move
// on to something else, you write std::move(s) once more.
//
// Classes get the same pair of overloads as special members: Message(Message&&)
// is the move constructor and operator=(Message&&) the move assignment, next to
// the copy versions. Mark moves noexcept when they can't throw (they usually
// just shuffle pointers): std::vector only moves its elements while growing if
// the move constructor promises not to throw. Otherwise it copies them.
//
// Often there's nothing to move at all:
// - `return Type(...);` builds the result directly in the caller's variable, and
//   `return local;` does too in practice ("copy elision"). Writing
//   return std::move(local) blocks that and costs a move.
// - v.emplace_back(args...) constructs the element inside the vector from
//   constructor arguments; v.push_back(Type(args...)) builds a temporary and
//   moves it in. v.reserve(n) avoids moves when the vector grows.
// - A "sink" parameter taken by value, like set_name(std::string name), is moved
//   to where it's kept. Callers passing a temporary pay one move; callers passing
//   a named variable pay one copy into the parameter, then the move.
//
// Read more: https://www.learncpp.com/cpp-tutorial/rvalue-references/
//            https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
//
// === Exercise: Copies and moves ==============================================
// Write the four copy/move operations, counting each one in the globals below,
// then the three functions underneath. Mark the two move operations noexcept
// once you've implemented them.
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

    // Copy other's text into the new message.
    // Add 1 to copies. other keeps its text.
    //
    // Example:
    //   Message original("hello");
    //   Message copy(original);
    //   // copy.text() and original.text() are both "hello"; copies is 1, moves is 0.
    Message(const Message& other) {
        throw "TODO";
    }

    // Move other's text into the new message with std::move.
    // Add 1 to moves.
    // Leave other's text empty: std::string's move usually does,
    // but other.text_.clear() guarantees it.
    //
    // Example:
    //   Message original("hello");
    //   Message moved(std::move(original));
    //   // moved.text() is "hello", original.text() is ""; moves is 1, copies is 0.
    //
    // The buffer changes owner instead of being duplicated.
    Message(Message&& other) {
        throw "TODO";
    }

    // Copy other's text into this existing message, replacing its old text.
    // Add 1 to copies, then return *this.
    //
    // Example:
    //   Message source("source");
    //   Message target("target");
    //   target = source;
    //   // target.text() and source.text() are both "source"; copies is 1.
    Message& operator=(const Message& other) {
        throw "TODO";
    }

    // Move other's text into this existing message, replacing its old text.
    // Add 1 to moves. Leave other's text empty, then return *this.
    //
    // Example:
    //   Message source("source");
    //   Message target("target");
    //   target = std::move(source);
    //   // target.text() is "source", source.text() is ""; moves is 1, copies is 0.
    Message& operator=(Message&& other) {
        throw "TODO";
    }

    const std::string& text() const { return text_; }

private:
    std::string text_;
};

// Add message to the end of box by moving it in.
// message is a "sink" parameter: it's taken by value, then moved into the box.
// A caller passing a temporary or std::move(x) pays for no copies at all.
//
// Example (counts for each call on its own):
//   box.reserve(4);                // room to spare, so the box never grows
//   store(box, Message("temp"));   // copies 0, moves 1
//   store(box, keep);              // copies 1, moves 1; keep still holds its text
//   store(box, std::move(give));   // copies 0, moves 2
//
// Inside store, message has a name, so moving it on needs std::move(message).
void store(std::vector<Message>& box, Message message) {
    throw "TODO";
}

// Return a new Message holding text.
// No copies or moves should happen: return a local by name (or a temporary)
// and the compiler builds it in place.
// `return std::move(local);` actually costs you a move.
//
// Example:
//   Message m = make_message("built in place");
//   // m.text() is "built in place"; copies is 0, moves is 0.
Message make_message(const std::string& text) {
    throw "TODO";
}

// Return n messages with the texts "message 1" ... "message n".
// Build them directly inside the vector so no Message is ever copied or moved:
// reserve() first, then emplace_back().
// n == 0 returns an empty vector.
//
// Example:
//   make_batch(3) holds "message 1", "message 2", "message 3"
//   // copies is 0, moves is 0.
//
// reserve() stops the vector from moving its elements when it grows.
std::vector<Message> make_batch(int n) {
    throw "TODO";
}
