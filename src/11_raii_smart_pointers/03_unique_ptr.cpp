// === Lesson: std::unique_ptr =================================================
//
// A std::unique_ptr<T> (from <memory>) is the sole owner of one heap object and
// deletes it in its destructor. It's RAII for `new`: you never write delete.
// Create one with std::make_unique, passing the constructor's arguments:
//
//     auto engine = std::make_unique<Engine>(150);   // std::unique_ptr<Engine>
//     engine->horsepower;          // use it like a pointer: ->, *, and if (engine)
//     Engine *raw = engine.get();  // a plain pointer to it; raw doesn't own it
//
// A unique_ptr can't be copied, since two owners would delete the object twice.
// It can be moved. std::move(p) marks p as "you may take from this", and a
// unique_ptr that's taken from hands the object over and is left null:
//
//     std::unique_ptr<Engine> copy = engine;   // error: copying is deleted
//     auto next = std::move(engine);           // next owns it; engine is null
//     next.reset();                            // deletes the Engine now
//
// Moves rearrange ownership without creating or destroying the object, including
// moves into and out of members:
//
//     struct Car { std::unique_ptr<Engine> engine; };
//
//     Car car{std::make_unique<Engine>(150)};
//     auto old = std::move(car.engine);             // old owns it; car.engine is null
//     car.engine = std::make_unique<Engine>(200);   // car owns a new one
//
// A function's signature says what it does with ownership:
//
//     std::unique_ptr<Engine> build();             // gives the caller ownership
//     void install(std::unique_ptr<Engine> e);     // takes ownership from the caller
//     void inspect(const Engine &e);               // just borrows the object
//
// Passing a named unique_ptr into install needs std::move(p): you're visibly
// giving it away. A temporary such as install(std::make_unique<Engine>(90))
// needs nothing. Returning a local unique_ptr is just `return p;`. A vector of
// unique_ptrs is fine too: push_back(std::move(p)), and moving an element out
// leaves a null pointer in its slot.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
//            https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/
//
// === Exercise: std::unique_ptr ===============================================
// Part 1 builds a stack from nodes that each own the next; part 2 passes
// Widgets' ownership around.
//
// ./grade 11_raii_smart_pointers/03_unique_ptr

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Part 1: a stack of ints as a chain of nodes. Each node owns the one below it,
// so destroying the head destroys the whole chain.
struct Node {
    int value;
    std::unique_ptr<Node> next;
};

class IntStack {
public:
    // Put value on top.
    //
    // Example:
    //   stack.push(1);
    //   stack.push(2);   // stack.top() == 2, stack.size() == 2
    //
    // Each node owns the one below it, so the new top node owns the old one.
    void push(int value) {
        throw "TODO";
    }

    // Remove the top value and return it, last in, first out.
    // Throw std::out_of_range when the stack is empty.
    //
    // Example:
    //   stack holds 1, 2, 3 (3 on top)
    //   stack.pop() == 3
    //   stack.pop() == 2   // now stack.size() == 1 and stack.top() == 1
    //
    // The removed node is deleted automatically once nothing owns it.
    int pop() {
        throw "TODO";
    }

    // Return the top value, without removing it.
    // Throw std::out_of_range when the stack is empty.
    //
    // Example:
    //   stack holds 1, 4 (4 on top)
    //   stack.top() == 4   // the stack is unchanged
    int top() const {
        throw "TODO";
    }

    int size() const {
        throw "TODO";
    }

    bool empty() const {
        throw "TODO";
    }

private:
    std::unique_ptr<Node> head_;  // the top node, or null when the stack is empty
    // TODO: any other members you need
};

// Part 2: passing ownership around. The tests count live widgets.
inline int widgets_alive = 0;

struct Widget {
    Widget(std::string widget_name, int widget_size) : name(std::move(widget_name)), size(widget_size) {
        ++widgets_alive;
    }
    ~Widget() { --widgets_alive; }
    Widget(const Widget &) = delete;
    Widget &operator=(const Widget &) = delete;

    std::string name;
    int size;
};

// Create a Widget on the heap and return the owning pointer.
//
// Example:
//   std::unique_ptr<Widget> widget = make_widget("gear", 3);
//   // widget->name == "gear", widget->size == 3, widgets_alive == 1
//   widget.reset();   // deletes the Widget, so widgets_alive == 0
//
// The caller owns the Widget, which is deleted when that unique_ptr dies or resets.
std::unique_ptr<Widget> make_widget(const std::string &name, int size) {
    throw "TODO";
}

// Take ownership of widget and keep it at the end of the shelf.
//
// Example:
//   auto widget = make_widget("bolt", 1);
//   adopt(shelf, std::move(widget));
//   // shelf.back()->name == "bolt", and widget is now null
//
// The shelf owns its widgets now, so they die with the shelf.
void adopt(std::vector<std::unique_ptr<Widget>> &shelf, std::unique_ptr<Widget> widget) {
    throw "TODO";
}

// Remove the widget at index from the shelf and hand ownership back to the caller.
// The shelf gets one shorter; the other widgets keep their order.
//
// Example:
//   shelf holds widgets "a", "b", "c"
//   std::unique_ptr<Widget> taken = take(shelf, 1);
//   // taken->name == "b", and shelf now holds "a", "c"
//
// Nothing is destroyed: the widget lives on until the caller lets go of it.
std::unique_ptr<Widget> take(std::vector<std::unique_ptr<Widget>> &shelf, std::size_t index) {
    throw "TODO";
}
