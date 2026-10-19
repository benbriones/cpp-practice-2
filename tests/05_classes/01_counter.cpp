#include "grader.hpp"
#include "05_classes/01_counter.cpp"

TEST("Counter: starts at zero by default") {
    Counter counter;
    CHECK_EQ(counter.value(), 0);
}

TEST("Counter: starts at the given value") {
    Counter counter(5);
    CHECK_EQ(counter.value(), 5);
}

TEST("increment: adds one by default") {
    Counter counter;
    counter.increment();
    counter.increment();
    counter.increment();
    CHECK_EQ(counter.value(), 3);
}

TEST("increment: uses the step") {
    Counter counter(10, 5);
    counter.increment();
    counter.increment();
    CHECK_EQ(counter.value(), 20);
}

TEST("decrement: subtracts the step") {
    Counter counter(10, 3);
    counter.decrement();
    CHECK_EQ(counter.value(), 7);
}

TEST("decrement: never goes below zero") {
    Counter counter(4, 3);
    counter.decrement();
    CHECK_EQ(counter.value(), 1);
    counter.decrement();
    CHECK_EQ(counter.value(), 0);
    counter.decrement();
    CHECK_EQ(counter.value(), 0);
}

TEST("reset: returns to the starting value") {
    Counter counter(2, 2);
    counter.increment();
    counter.increment();
    counter.reset();
    CHECK_EQ(counter.value(), 2);
    counter.decrement();
    counter.reset();
    CHECK_EQ(counter.value(), 2);
}

TEST("Counter: rejects a step that isn't positive") {
    CHECK_THROWS(std::invalid_argument, Counter(0, 0));
    CHECK_THROWS(std::invalid_argument, Counter(3, -1));
}

TEST("Counter: rejects a negative start") {
    CHECK_THROWS(std::invalid_argument, Counter(-1));
}

TEST("value: readable through a const reference") {
    Counter counter(7);
    counter.increment();
    const Counter& view = counter;
    CHECK_EQ(view.value(), 8);
}

TEST("Counters are independent objects") {
    Counter a;
    Counter b(100, 10);
    a.increment();
    b.increment();
    CHECK_EQ(a.value(), 1);
    CHECK_EQ(b.value(), 110);
}
