#include "grader.hpp"
#include "03c_even_more_references_pointers/04_pointer_parameters.cpp"

namespace {

void set_target(int **pp, int *target) { *pp = target; }
void bump_target(int **pp) { **pp += 1; }
void lose_target(int *p) { p = nullptr; }

}  // namespace

TEST("trace_6: x, y and *p at the end") {
    int x = 1;
    int y = 10;
    int *p = &x;
    bump_target(&p);
    set_target(&p, &y);
    bump_target(&p);
    lose_target(p);
    *p *= 2;
    CHECK_EQ(trace_6(), {x, y, *p});
}

TEST("sum_or: sums the vector") {
    std::vector<int> values{1, 2, 3};
    CHECK_EQ(sum_or(&values, -1), 6);
    std::vector<int> negatives{-4, 1};
    CHECK_EQ(sum_or(&negatives, 100), -3);
}

TEST("sum_or: fallback for nullptr") {
    CHECK_EQ(sum_or(nullptr, -1), -1);
    CHECK_EQ(sum_or(nullptr, 42), 42);
}

TEST("sum_or: an empty vector is not missing") {
    std::vector<int> empty;
    CHECK(sum_or(&empty, -1) == 0, "values points at a real, empty vector: sum it, don't fall back");
}

TEST("push_clamped: under the limit") {
    std::vector<int> values;
    int cap = 10;
    push_clamped(&values, 4, &cap);
    push_clamped(&values, 10, &cap);
    CHECK_EQ(values, {4, 10});
}

TEST("push_clamped: over the limit appends the limit") {
    std::vector<int> values{1};
    int cap = 10;
    push_clamped(&values, 50, &cap);
    CHECK_EQ(values, {1, 10});
    int negative_cap = -3;
    push_clamped(&values, 0, &negative_cap);
    CHECK_EQ(values, {1, 10, -3});
}

TEST("push_clamped: nullptr means no limit") {
    std::vector<int> values;
    push_clamped(&values, 50, nullptr);
    push_clamped(&values, -50, nullptr);
    CHECK_EQ(values, {50, -50});
}

TEST("push_clamped: leaves the limit alone") {
    std::vector<int> values;
    int cap = 10;
    push_clamped(&values, 50, &cap);
    CHECK_EQ(cap, 10);
}

TEST("swap_pointers: swaps targets, not ints") {
    int x = 1;
    int y = 2;
    int *p = &x;
    int *q = &y;
    swap_pointers(&p, &q);
    CHECK(p == &y, "p should now point at y");
    CHECK(q == &x, "q should now point at x");
    CHECK_EQ(x, 1);
    CHECK_EQ(y, 2);
}

TEST("swap_pointers: twice puts them back") {
    int x = 1;
    int y = 2;
    int *p = &x;
    int *q = &y;
    swap_pointers(&p, &q);
    swap_pointers(&p, &q);
    CHECK(p == &x, "after two swaps p should point at x again");
    CHECK(q == &y, "after two swaps q should point at y again");
}

TEST("swap_pointers: a nullptr can be swapped in") {
    int x = 1;
    int *p = &x;
    int *q = nullptr;
    swap_pointers(&p, &q);
    CHECK(p == nullptr, "p should now hold q's old value, nullptr");
    CHECK(q == &x, "q should now point at x");
}

TEST("point_at_max: points at the largest element") {
    std::vector<int> values{3, 9, 4};
    int *best = nullptr;
    CHECK_EQ(point_at_max(values, &best), true);
    CHECK(best == &values[1], "best should point at values[1] itself");
}

TEST("point_at_max: the first of a tie, and negatives") {
    std::vector<int> values{3, 9, 4, 9};
    int *best = nullptr;
    point_at_max(values, &best);
    CHECK(best == &values[1], "9 appears twice: best should point at the first one, values[1]");
    std::vector<int> negatives{-5, -2, -8};
    point_at_max(negatives, &best);
    CHECK(best == &negatives[1], "-2 is the largest");
}

TEST("point_at_max: writing through the result") {
    std::vector<int> values{3, 9, 4};
    int *best = nullptr;
    point_at_max(values, &best);
    *best = 0;
    CHECK_EQ(values, {3, 0, 4});
}

TEST("point_at_max: empty leaves the pointer alone") {
    std::vector<int> empty;
    int x = 5;
    int *best = &x;
    CHECK_EQ(point_at_max(empty, &best), false);
    CHECK(best == &x, "values is empty, so best should still point at x");
}
