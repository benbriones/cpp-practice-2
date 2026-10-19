#include "grader.hpp"
#include "15_templates/02_class_templates.cpp"

#include <string>
#include <type_traits>

TEST("Stack: last in, first out") {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    CHECK_EQ(stack.pop(), 3);
    CHECK_EQ(stack.pop(), 2);
    stack.push(4);
    CHECK_EQ(stack.pop(), 4);
    CHECK_EQ(stack.pop(), 1);
}

TEST("Stack: top, size, empty") {
    Stack<std::string> stack;
    CHECK(stack.empty());
    CHECK_EQ(stack.size(), 0);
    stack.push("a");
    stack.push("b");
    CHECK_EQ(stack.top(), "b");
    CHECK_EQ(stack.size(), 2);
    CHECK(!stack.empty());
}

TEST("Stack: pop and top on an empty stack throw std::out_of_range") {
    Stack<int> stack;
    CHECK_THROWS(std::out_of_range, stack.pop());
    CHECK_THROWS(std::out_of_range, stack.top());
}

TEST("RingBuffer: holds values until full") {
    RingBuffer<int, 3> buffer;
    CHECK_EQ(buffer.size(), 0);
    buffer.push(10);
    buffer.push(20);
    CHECK_EQ(buffer.size(), 2);
    CHECK_EQ(buffer.to_vector(), {10, 20});
}

TEST("RingBuffer: overwrites the oldest value when full") {
    RingBuffer<int, 3> buffer;
    for (int i = 1; i <= 5; ++i) buffer.push(i);
    CHECK_EQ(buffer.size(), 3);
    CHECK_EQ(buffer.to_vector(), {3, 4, 5});
}

TEST("RingBuffer: at(0) is the oldest") {
    RingBuffer<std::string, 2> buffer;
    buffer.push("a");
    buffer.push("b");
    buffer.push("c");
    CHECK_EQ(buffer.at(0), "b");
    CHECK_EQ(buffer.at(1), "c");
}

TEST("RingBuffer: wraps around many times") {
    RingBuffer<int, 4> buffer;
    for (int i = 1; i <= 103; ++i) buffer.push(i);
    CHECK_EQ(buffer.to_vector(), {100, 101, 102, 103});
}

TEST("RingBuffer: at() past size() throws std::out_of_range") {
    RingBuffer<int, 5> buffer;
    buffer.push(7);
    CHECK_EQ(buffer.at(0), 7);
    CHECK_THROWS(std::out_of_range, buffer.at(1));
    CHECK_THROWS(std::out_of_range, buffer.at(5));
}

TEST("RingBuffer: capacity() is N") {
    RingBuffer<int, 4> four;
    RingBuffer<double, 1> one;
    CHECK_EQ(four.capacity(), 4);
    CHECK_EQ(one.capacity(), 1);
}

TEST("Pair: stores two values of different types") {
    Pair point{3, 2.5};
    CHECK_EQ(point.first, 3);
    CHECK_NEAR(point.second, 2.5);
}

TEST("Pair: template arguments are deduced from the constructor") {
    Pair entry{std::string("id"), 42};
    CHECK((std::is_same_v<decltype(entry), Pair<std::string, int>>));
    CHECK_EQ(entry.first, "id");
    CHECK_EQ(entry.second, 42);
}

TEST("Pair: swapped") {
    const Pair original{1, std::string("one")};
    auto flipped = original.swapped();
    CHECK((std::is_same_v<decltype(flipped), Pair<std::string, int>>));
    CHECK_EQ(flipped.first, "one");
    CHECK_EQ(flipped.second, 1);
    CHECK_EQ(original.first, 1);
}
