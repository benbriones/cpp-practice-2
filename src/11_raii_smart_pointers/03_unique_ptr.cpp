// Exercise: std::unique_ptr
// A std::unique_ptr owns one heap object and deletes it automatically. It can't
// be copied, only moved: `b = std::move(a);` hands ownership to b and leaves a null.
//
//   auto p = std::make_unique<Widget>("gear", 3);   p->name;   if (p) { ... }
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
    void push(int value) {
        throw "TODO";
    }

    // Remove and return the top value. Throw std::out_of_range when empty.
    int pop() {
        throw "TODO";
    }

    // The top value, without removing it. Throw std::out_of_range when empty.
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
    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;

    std::string name;
    int size;
};

// Create a Widget on the heap and return the owning pointer.
std::unique_ptr<Widget> make_widget(const std::string& name, int size) {
    throw "TODO";
}

// Take ownership of widget and keep it at the end of the shelf.
void adopt(std::vector<std::unique_ptr<Widget>>& shelf, std::unique_ptr<Widget> widget) {
    throw "TODO";
}

// Remove the widget at index from the shelf and hand ownership back to the caller.
std::unique_ptr<Widget> take(std::vector<std::unique_ptr<Widget>>& shelf, std::size_t index) {
    throw "TODO";
}
