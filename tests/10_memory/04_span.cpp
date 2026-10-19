#include <array>

#include "grader.hpp"
#include "10_memory/04_span.cpp"

TEST("sum: works for a C array, std::array, and std::vector") {
    const int c_array[] = {1, 2, 3};
    const std::array<int, 4> std_array{10, 20, 30, 40};
    const std::vector<int> vec{5, -5, 7};
    CHECK_EQ(sum(c_array), 6);
    CHECK_EQ(sum(std_array), 100);
    CHECK_EQ(sum(vec), 7);
}

TEST("sum: empty spans and sub-spans") {
    const std::vector<int> vec{1, 2, 3, 4};
    CHECK_EQ(sum(std::span<const int>()), 0);
    CHECK_EQ(sum(std::span<const int>(vec).first(2)), 3);
}

TEST("middle: even leftover") {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::span<int> mid = middle(vec, 2);
    CHECK_EQ(std::vector<int>(mid.begin(), mid.end()), {3, 4});
}

TEST("middle: odd leftover puts the extra element at the end") {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::span<int> mid = middle(vec, 3);
    CHECK_EQ(std::vector<int>(mid.begin(), mid.end()), {2, 3, 4});
}

TEST("middle: n too big gives the whole span") {
    std::vector<int> vec{1, 2, 3};
    std::span<int> all = middle(vec, 10);
    CHECK_EQ(std::vector<int>(all.begin(), all.end()), {1, 2, 3});
}

TEST("middle: views the original memory") {
    int c_array[] = {10, 20, 30, 40, 50};
    std::span<int> mid = middle(c_array, 1);
    CHECK(mid.data() == &c_array[2], "middle() should point into the original array");
    mid[0] = 0;
    CHECK_EQ(c_array[2], 0);
}

TEST("fill_table") {
    int grid[kRows][kCols] = {};
    fill_table(grid);
    CHECK_EQ(std::vector<int>(grid[0], grid[0] + kCols), {1, 2, 3, 4});
    CHECK_EQ(std::vector<int>(grid[1], grid[1] + kCols), {2, 4, 6, 8});
    CHECK_EQ(std::vector<int>(grid[2], grid[2] + kCols), {3, 6, 9, 12});
}

TEST("column_sum") {
    const int grid[kRows][kCols] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, -12},
    };
    CHECK_EQ(column_sum(grid, 0), 15);
    CHECK_EQ(column_sum(grid, 1), 18);
    CHECK_EQ(column_sum(grid, 3), 0);
}
