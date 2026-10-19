// === Lesson: Grids ===========================================================
//
// The everyday way to store a grid is a vector of rows, indexed grid[row][col]:
//
//     std::vector<std::vector<int>> table{
//         {1, 2, 3},
//         {4, 5, 6},
//     };
//     table[1][2];          // 6: row 1, column 2
//     table.size();         // 2 rows
//     table[0].size();      // 3 columns (only if there's a row 0)
//
// A grid of characters is a vector of strings, one string per row:
//
//     std::vector<std::string> maze{"#.#", "..#"};
//     maze[0][1];           // '.'
//
// To make a grid of a given size, use the (count, value) constructor with a
// whole row as the value:
//
//     std::vector<std::vector<int>> zeros(rows, std::vector<int>(cols, 0));
//     std::vector<std::string> blank(rows, std::string(cols, '.'));
//
// Nested loops visit every cell, row by row:
//
//     std::vector<std::string> checkerboard(int rows, int cols) {
//         std::vector<std::string> board(rows, std::string(cols, '.'));
//         for (int r = 0; r < rows; ++r) {
//             for (int c = 0; c < cols; ++c) {
//                 if ((r + c) % 2 == 0) {
//                     board[r][c] = '#';
//                 }
//             }
//         }
//         return board;
//     }
//
// Looking at a cell's neighbours means indexes like r - 1 and c + 1, which can
// fall off the edge. Indexing outside a vector or string is undefined behavior,
// and not every such read gets caught, so check before you index. Signed ints
// keep that check simple (r >= 0 && r < rows); with std::size_t, r - 1 at
// r == 0 wraps around to a huge number instead of -1.
//
// Copying a whole grid is one assignment, and the copy is independent:
//
//     std::vector<std::string> before = board;   // board can change; before won't
//
// Read more: https://en.cppreference.com/w/cpp/container/vector/vector
//            https://www.learncpp.com/cpp-tutorial/multidimensional-c-style-arrays/
//
// === Exercise: Grids =========================================================
// Implement the three functions below.
//
// ./grade 02_strings_vectors/04_grids

#include <string>
#include <vector>

// Rows become columns: {{1, 2, 3}, {4, 5, 6}} becomes {{1, 4}, {2, 5}, {3, 6}}.
// The matrix is rectangular; an empty matrix gives an empty result.
std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>>& matrix) {
    throw "TODO";
}

// In a grid of '#' (alive) and '.' (dead) cells, count the live cells among
// the 8 neighbours of (row, col). Cells past the edge don't exist; there's no
// wrap-around.
int count_neighbors(const std::vector<std::string>& grid, int row, int col) {
    throw "TODO";
}

// One generation of Conway's Game of Life, as a new grid:
//   a live cell with 2 or 3 live neighbours stays alive, otherwise it dies;
//   a dead cell with exactly 3 live neighbours comes alive.
// Every cell updates at once, so count neighbours in the old grid only.
std::vector<std::string> life_step(const std::vector<std::string>& grid) {
    throw "TODO";
}
