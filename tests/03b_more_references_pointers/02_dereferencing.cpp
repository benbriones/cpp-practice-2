#include "grader.hpp"
#include "03b_more_references_pointers/02_dereferencing.cpp"

TEST("trace_3: assigning to a reference") {
    int x = 1;
    int y = 2;
    int &r = x;
    r = y;
    r = 30;
    y = 40;
    CHECK_EQ(trace_3(), {x, y});
}

TEST("trace_4: incrementing through a pointer") {
    int n = 5;
    int *p = &n;
    ++*p;
    (*p)++;
    *p = *p * 10;
    int m = *p;
    m += 1;
    CHECK_EQ(trace_4(), {n, m});
}

TEST("rotate_three: rotates left") {
    int x = 1;
    int y = 2;
    int z = 3;
    rotate_three(&x, &y, &z);
    CHECK_EQ(x, 2);
    CHECK_EQ(y, 3);
    CHECK_EQ(z, 1);
}

TEST("rotate_three: twice") {
    int x = 1;
    int y = 2;
    int z = 3;
    rotate_three(&x, &y, &z);
    rotate_three(&x, &y, &z);
    CHECK_EQ(x, 3);
    CHECK_EQ(y, 1);
    CHECK_EQ(z, 2);
}

TEST("rotate_three: vector elements, in either order") {
    std::vector<int> values{10, 20, 30};
    rotate_three(&values[0], &values[1], &values[2]);
    CHECK_EQ(values, {20, 30, 10});
    std::vector<int> others{10, 20, 30};
    rotate_three(&others[2], &others[1], &others[0]);
    CHECK_EQ(others, {30, 10, 20});
}

TEST("add_to_each: adds to every target") {
    int x = 1;
    int y = 2;
    add_to_each({&x, &y}, 10);
    CHECK_EQ(x, 11);
    CHECK_EQ(y, 12);
}

TEST("add_to_each: skips nullptrs") {
    int x = 1;
    add_to_each({nullptr, &x, nullptr}, 5);
    CHECK_EQ(x, 6);
    add_to_each({nullptr}, 5);
    add_to_each({}, 5);
    CHECK_EQ(x, 6);
}

TEST("add_to_each: a repeated pointer adds twice") {
    int x = 0;
    int y = 0;
    add_to_each({&x, &y, &x}, 3);
    CHECK_EQ(x, 6);
    CHECK_EQ(y, 3);
}

TEST("add_to_each: pointers into a vector") {
    std::vector<int> values{1, 2, 3};
    add_to_each({&values[0], &values[2]}, -1);
    CHECK_EQ(values, {0, 2, 2});
}

TEST("larger_of: points at the larger") {
    int x = 3;
    int y = 8;
    CHECK(larger_of(&x, &y) == &y, "8 is larger, so the result should be &y");
    CHECK(larger_of(&y, &x) == &y, "8 is larger, so the result should be &y");
}

TEST("larger_of: a on ties, and negatives") {
    int x = -4;
    int y = -4;
    CHECK(larger_of(&x, &y) == &x, "on a tie, the result should be a (&x here)");
    int z = -9;
    CHECK(larger_of(&z, &x) == &x, "-4 is larger than -9, so the result should be &x");
}

TEST("larger_of: writing through the result") {
    int x = 3;
    int y = 8;
    *larger_of(&x, &y) = 0;
    CHECK_EQ(x, 3);
    CHECK_EQ(y, 0);
}
