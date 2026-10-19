// Exercise: std::span and 2D arrays
// std::span<T> (C++20, <span>) is a view of elements stored side by side: a
// pointer plus a size, owning nothing. C arrays, std::array, and std::vector
// all convert to it, so one function serves all three without losing the size.
// std::span<const int> is read-only; std::span<int> can write through.
//
// Grade: grade 10_memory/04_span

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
