#include "grader.hpp"
#include "07_algorithms_lambdas/01_lambdas.cpp"

static int subtract(int a, int b) { return a - b; }

TEST("make_multiplier") {
    auto triple = make_multiplier(3);
    CHECK_EQ(triple(5), 15);
    CHECK_EQ(triple(-2), -6);
    CHECK_EQ(make_multiplier(0)(42), 0);
}

TEST("make_multiplier: each function keeps its own factor") {
    auto twice = make_multiplier(2);
    auto ten_times = make_multiplier(10);
    CHECK_EQ(twice(7), 14);
    CHECK_EQ(ten_times(7), 70);
}

TEST("make_counter: counts up from 1") {
    auto next = make_counter();
    CHECK_EQ(next(), 1);
    CHECK_EQ(next(), 2);
    CHECK_EQ(next(), 3);
}

TEST("make_counter: counters are independent") {
    auto first = make_counter();
    auto second = make_counter();
    first();
    first();
    CHECK_EQ(second(), 1);
    CHECK_EQ(first(), 3);
}

TEST("apply_n_times") {
    auto add_three = [](int x) { return x + 3; };
    CHECK_EQ(apply_n_times(add_three, 4, 0), 12);
    CHECK_EQ(apply_n_times(make_multiplier(2), 10, 1), 1024);
}

TEST("apply_n_times: zero times") {
    CHECK_EQ(apply_n_times([](int x) { return x * 100; }, 0, 7), 7);
}

TEST("compose: applies g first, then f") {
    auto add_one = [](int x) { return x + 1; };
    auto double_it = [](int x) { return x * 2; };
    CHECK_EQ(compose(add_one, double_it)(5), 11);
    CHECK_EQ(compose(double_it, add_one)(5), 12);
}

TEST("count_where: with a capturing lambda") {
    const std::vector<int> values{5, 12, 7, 20, 3, 15};
    int threshold = 10;
    CHECK_EQ(count_where(values, [threshold](int x) { return x > threshold; }), 3);
    CHECK_EQ(count_where(values, [](int x) { return x % 2 == 1; }), 4);
    CHECK_EQ(count_where({}, [](int) { return true; }), 0);
}

TEST("fold: with a lambda") {
    CHECK_EQ(fold({1, 2, 3, 4}, 0, [](int a, int b) { return a + b; }), 10);
    CHECK_EQ(fold({1, 2, 3, 4}, 1, [](int a, int b) { return a * b; }), 24);
}

TEST("fold: with a named function, left to right") {
    CHECK_EQ(fold({1, 2, 3}, 10, subtract), 4);
    CHECK_EQ(fold({}, 10, subtract), 10);
}
