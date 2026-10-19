#include "grader.hpp"
#include "02_strings_vectors/04_grids.cpp"

TEST("transpose: rectangle") {
    CHECK_EQ(transpose({{1, 2, 3}, {4, 5, 6}}), {{1, 4}, {2, 5}, {3, 6}});
}

TEST("transpose: square, row, column") {
    CHECK_EQ(transpose({{1, 2}, {3, 4}}), {{1, 3}, {2, 4}});
    CHECK_EQ(transpose({{7, 8, 9}}), {{7}, {8}, {9}});
    CHECK_EQ(transpose({{7}, {8}, {9}}), {{7, 8, 9}});
}

TEST("transpose: empty matrix") {
    CHECK_EQ(transpose({}), {});
}

TEST("count_neighbors: middle of the grid") {
    const std::vector<std::string> grid{
        "#.#",
        ".#.",
        "###",
    };
    CHECK_EQ(count_neighbors(grid, 1, 1), 5);
    CHECK_EQ(count_neighbors(grid, 0, 1), 3);
}

TEST("count_neighbors: corners and edges don't wrap") {
    const std::vector<std::string> grid{
        "#..#",
        "....",
        "#..#",
    };
    CHECK_EQ(count_neighbors(grid, 0, 0), 0);
    CHECK_EQ(count_neighbors(grid, 1, 0), 2);
    CHECK_EQ(count_neighbors(grid, 2, 3), 0);
    CHECK_EQ(count_neighbors(grid, 1, 1), 2);
}

TEST("count_neighbors: doesn't count the cell itself") {
    const std::vector<std::string> grid{"#"};
    CHECK_EQ(count_neighbors(grid, 0, 0), 0);
}

TEST("life_step: a block never changes") {
    const std::vector<std::string> block{
        "....",
        ".##.",
        ".##.",
        "....",
    };
    CHECK_EQ(life_step(block), block);
}

TEST("life_step: a blinker flips between two shapes") {
    const std::vector<std::string> horizontal{
        ".....",
        ".....",
        ".###.",
        ".....",
        ".....",
    };
    const std::vector<std::string> vertical{
        ".....",
        "..#..",
        "..#..",
        "..#..",
        ".....",
    };
    CHECK_EQ(life_step(horizontal), vertical);
    CHECK_EQ(life_step(vertical), horizontal);
}

TEST("life_step: lonely and crowded cells die") {
    CHECK_EQ(life_step({"...", ".#.", "..."}), {"...", "...", "..."});
    CHECK_EQ(life_step({"###", "###", "###"}), {"#.#", "...", "#.#"});
}

TEST("life_step: a glider moves diagonally after 4 steps") {
    std::vector<std::string> grid{
        ".#....",
        "..#...",
        "###...",
        "......",
        "......",
        "......",
    };
    for (int i = 0; i < 4; ++i) grid = life_step(grid);
    CHECK_EQ(grid, {
                       "......",
                       "..#...",
                       "...#..",
                       ".###..",
                       "......",
                       "......",
                   });
}
