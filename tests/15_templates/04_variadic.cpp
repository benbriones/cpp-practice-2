#include "grader.hpp"
#include "15_templates/04_variadic.cpp"

#include <string>

TEST("count_args") {
    CHECK_EQ(count_args(), 0);
    CHECK_EQ(count_args(42), 1);
    CHECK_EQ(count_args(1, "two", 3.0, 'c'), 4);
}

TEST("sum_all: ints") {
    CHECK_EQ(sum_all(1, 2, 3), 6);
    CHECK_EQ(sum_all(5), 5);
    CHECK_EQ(sum_all(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10), -55);
}

TEST("sum_all: mixed numbers become a double") {
    CHECK_NEAR(sum_all(1, 2.5), 3.5);
    CHECK_NEAR(sum_all(0.25, 1, 2LL), 3.25);
}

TEST("sum_all: strings concatenate") {
    CHECK_EQ(sum_all(std::string("ab"), std::string("cd"), std::string("e")), "abcde");
}

TEST("all_true") {
    CHECK_EQ(all_true(true, true, true), true);
    CHECK_EQ(all_true(true, false, true), false);
    CHECK_EQ(all_true(1, 2, 3), true);
    CHECK_EQ(all_true(1, 0), false);
}

TEST("all_true: no arguments") {
    CHECK_EQ(all_true(), true);
}

TEST("any_equal") {
    CHECK_EQ(any_equal(3, 1, 2, 3), true);
    CHECK_EQ(any_equal(9, 1, 2, 3), false);
    CHECK_EQ(any_equal(std::string("b"), "a", "b"), true);
}

TEST("any_equal: nothing to compare against") {
    CHECK_EQ(any_equal(5), false);
}

TEST("join_all: mixed types") {
    CHECK_EQ(join_all(", ", 1, "two", 3.5), "1, two, 3.5");
    CHECK_EQ(join_all("/", "usr", "local", "bin"), "usr/local/bin");
}

TEST("join_all: zero or one argument") {
    CHECK_EQ(join_all("-"), "");
    CHECK_EQ(join_all("-", 'x'), "x");
}

TEST("join_all: empty separator") {
    CHECK_EQ(join_all("", 1, 2, 3), "123");
}
