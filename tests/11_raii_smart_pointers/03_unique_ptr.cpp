#include "grader.hpp"
#include "11_raii_smart_pointers/03_unique_ptr.cpp"

TEST("IntStack: push and top") {
    IntStack stack;
    stack.push(1);
    stack.push(2);
    CHECK_EQ(stack.top(), 2);
    CHECK_EQ(stack.size(), 2);
}

TEST("IntStack: pop returns values last-in, first-out") {
    IntStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    CHECK_EQ(stack.pop(), 3);
    CHECK_EQ(stack.pop(), 2);
    CHECK_EQ(stack.size(), 1);
    CHECK_EQ(stack.top(), 1);
}

TEST("IntStack: empty()") {
    IntStack stack;
    CHECK_EQ(stack.empty(), true);
    stack.push(5);
    CHECK_EQ(stack.empty(), false);
    stack.pop();
    CHECK_EQ(stack.empty(), true);
    CHECK_EQ(stack.size(), 0);
}

TEST("IntStack: pop and top throw on an empty stack") {
    IntStack stack;
    CHECK_THROWS(std::out_of_range, stack.pop());
    CHECK_THROWS(std::out_of_range, stack.top());
}

TEST("IntStack: top() works on a const stack") {
    IntStack stack;
    stack.push(4);
    const IntStack& view = stack;
    CHECK_EQ(view.top(), 4);
    CHECK_EQ(view.size(), 1);
}

TEST("IntStack: a thousand pushes and pops") {
    IntStack stack;
    for (int i = 0; i < 1000; ++i) stack.push(i);
    CHECK_EQ(stack.size(), 1000);
    long long total = 0;
    while (!stack.empty()) total += stack.pop();
    CHECK_EQ(total, 499'500LL);
}

TEST("make_widget: returns an owning pointer") {
    std::unique_ptr<Widget> widget = make_widget("gear", 3);
    CHECK(widget != nullptr);
    CHECK_EQ(widget->name, "gear");
    CHECK_EQ(widget->size, 3);
    CHECK_EQ(widgets_alive, 1);
    widget.reset();
    CHECK_EQ(widgets_alive, 0);
}

TEST("adopt: the shelf takes ownership") {
    std::vector<std::unique_ptr<Widget>> shelf;
    auto widget = make_widget("bolt", 1);
    adopt(shelf, std::move(widget));
    CHECK(widget == nullptr, "after std::move, the caller's pointer should be null");
    CHECK_EQ(shelf.size(), 1u);
    CHECK_EQ(shelf[0]->name, "bolt");
    CHECK_EQ(widgets_alive, 1);
}

TEST("adopt: widgets die with the shelf") {
    {
        std::vector<std::unique_ptr<Widget>> shelf;
        adopt(shelf, make_widget("a", 1));
        adopt(shelf, make_widget("b", 2));
        CHECK_EQ(widgets_alive, 2);
    }
    CHECK_EQ(widgets_alive, 0);
}

TEST("take: hands ownership back") {
    std::vector<std::unique_ptr<Widget>> shelf;
    adopt(shelf, make_widget("a", 1));
    adopt(shelf, make_widget("b", 2));
    adopt(shelf, make_widget("c", 3));
    std::unique_ptr<Widget> taken = take(shelf, 1);
    CHECK_EQ(taken->name, "b");
    CHECK_EQ(shelf.size(), 2u);
    CHECK_EQ(shelf[0]->name, "a");
    CHECK_EQ(shelf[1]->name, "c");
    CHECK_EQ(widgets_alive, 3);
    taken.reset();
    CHECK_EQ(widgets_alive, 2);
}
