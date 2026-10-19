// Exercise: Grids
// Two-dimensional data as a vector of rows: std::vector<std::vector<int>>, or
// std::vector<std::string> for a grid of characters. grid[row][col].
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
