// === Lesson: std::span and 2D arrays =========================================
//
// std::span<T> (C++20, <span>) is a view of elements stored side by side: just
// a pointer and a size, owning nothing. It plays the role for arrays that
// std::string_view plays for strings. A C array, a std::array and a std::vector
// all convert to a span automatically, so one function accepts all three and
// still knows how many elements it got:
//
//     void scale(std::span<double> xs, double k) {
//         for (double& x : xs) x *= k;          // writes through to the caller's data
//     }
//     std::vector<double> prices{1, 2, 3, 4};
//     double raw[3] = {1, 1, 1};
//     scale(prices, 2);                         // prices is {2, 4, 6, 8}
//     scale(raw, 10);                           // raw is {10, 10, 10}
//
// std::span<const T> is read-only; std::span<T> can change the elements. Pass a
// span by value: it's two words, and copying it never copies the elements.
//
// A span supports size(), empty(), [i], data() and range-for, and can be cut
// into smaller views of the same memory:
//
//     std::span<double> all(prices);
//     all.first(2)          // the first 2 elements
//     all.last(2)           // the last 2
//     all.subspan(1, 2)     // 2 elements starting at index 1
//
// Because a span doesn't own its elements, it must not outlive them. A span of
// a vector that later grows (and reallocates) or dies is dangling, just like a
// string_view of a dead string.
//
// 2D arrays. int grid[3][4] is an array of 3 rows, each an array of 4 ints,
// stored row after row in one block. grid[r] is row r, and grid[r][c] one cell:
//
//     char board[3][3] = {{'x', 'o', 'x'}, {' ', 'x', 'o'}, {'o', ' ', 'x'}};
//     for (int r = 0; r < 3; ++r) {
//         for (int c = 0; c < 3; ++c) std::cout << board[r][c];
//         std::cout << '\n';
//     }
//
// Passed to a function, a 2D array decays like any array, to a pointer to its
// first row. Only the outer size is lost: the parameter must still spell out the
// row length (int grid[][4] or int grid[3][4]), so the compiler knows how far
// apart the rows are.
//
// Read more: https://en.cppreference.com/w/cpp/container/span
//            https://www.learncpp.com/cpp-tutorial/multidimensional-c-style-arrays/
//
// === Exercise: std::span and 2D arrays =======================================
// Implement the four functions below.
//
// ./grade 10_memory/04_span

#include <cstddef>
#include <span>

int sum(std::span<const int> values) {
    throw "TODO";
}

// The middle n elements, as a view of the same memory: skip (size - n) / 2
// elements at the front. If n >= size, return the whole span.
// middle({1, 2, 3, 4, 5, 6}, 2) views {3, 4}.  Hint: values.subspan(offset, count)
std::span<int> middle(std::span<int> values, std::size_t n) {
    throw "TODO";
}

// A 2D C array: int grid[3][4] is 3 rows of 4 ints, stored back to back.
constexpr int kRows = 3;
constexpr int kCols = 4;

// Fill a multiplication table: grid[r][c] = (r + 1) * (c + 1).
void fill_table(int grid[kRows][kCols]) {
    throw "TODO";
}

// Sum of column `col` (0-based).
int column_sum(const int grid[kRows][kCols], int col) {
    throw "TODO";
}
