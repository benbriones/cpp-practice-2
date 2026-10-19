#include "grader.hpp"
#include "03_references_pointers/01_references.cpp"

TEST("swap_ints: exchanges two variables") {
    int a = 1;
    int b = 2;
    swap_ints(a, b);
    CHECK_EQ(a, 2);
    CHECK_EQ(b, 1);
}

TEST("swap_ints: negative and equal values") {
    int a = -5;
    int b = 7;
    swap_ints(a, b);
    CHECK_EQ(a, 7);
    CHECK_EQ(b, -5);
    int c = 3;
    int d = 3;
    swap_ints(c, d);
    CHECK_EQ(c, 3);
    CHECK_EQ(d, 3);
}

TEST("swap_ints: a variable with itself") {
    int a = 42;
    swap_ints(a, a);
    CHECK_EQ(a, 42);
}

TEST("double_all: changes the caller's vector") {
    std::vector<int> values{1, -2, 3};
    double_all(values);
    CHECK_EQ(values, {2, -4, 6});
}

TEST("double_all: empty vector") {
    std::vector<int> values;
    double_all(values);
    CHECK_EQ(values, {});
}

TEST("min_max: writes both results") {
    int lo = -999;
    int hi = -999;
    min_max({4, 9, 1, 7}, lo, hi);
    CHECK_EQ(lo, 1);
    CHECK_EQ(hi, 9);
}

TEST("min_max: negatives and a single element") {
    int lo = 0;
    int hi = 0;
    min_max({-3, -8, -1}, lo, hi);
    CHECK_EQ(lo, -8);
    CHECK_EQ(hi, -1);
    min_max({5}, lo, hi);
    CHECK_EQ(lo, 5);
    CHECK_EQ(hi, 5);
}

TEST("largest: refers to the element inside the vector") {
    std::vector<int> values{3, 8, 5};
    int& big = largest(values);
    CHECK_EQ(big, 8);
    CHECK(&big == &values[1], "largest should return a reference to values[1], not to a copy");
}

TEST("largest: assigning through the result changes the vector") {
    std::vector<int> values{3, 8, 5};
    largest(values) = 0;
    CHECK_EQ(values, {3, 0, 5});
    largest(values) += 100;
    CHECK_EQ(values, {3, 0, 105});
}

TEST("largest: first one on ties") {
    std::vector<int> values{2, 9, 9, 1};
    largest(values) = -1;
    CHECK_EQ(values, {2, -1, 9, 1});
}
