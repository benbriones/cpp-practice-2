#include "grader.hpp"
#include "04_structs_enums/02_enums.cpp"

TEST("turn_right: every direction") {
    CHECK_EQ(turn_right(Direction::North), Direction::East);
    CHECK_EQ(turn_right(Direction::East), Direction::South);
    CHECK_EQ(turn_right(Direction::South), Direction::West);
    CHECK_EQ(turn_right(Direction::West), Direction::North);
}

TEST("turn_left: every direction") {
    CHECK_EQ(turn_left(Direction::North), Direction::West);
    CHECK_EQ(turn_left(Direction::West), Direction::South);
    CHECK_EQ(turn_left(Direction::South), Direction::East);
    CHECK_EQ(turn_left(Direction::East), Direction::North);
}

TEST("opposite: every direction") {
    CHECK_EQ(opposite(Direction::North), Direction::South);
    CHECK_EQ(opposite(Direction::South), Direction::North);
    CHECK_EQ(opposite(Direction::East), Direction::West);
    CHECK_EQ(opposite(Direction::West), Direction::East);
}

TEST("to_string: every direction") {
    CHECK_EQ(to_string(Direction::North), "North");
    CHECK_EQ(to_string(Direction::East), "East");
    CHECK_EQ(to_string(Direction::South), "South");
    CHECK_EQ(to_string(Direction::West), "West");
}

TEST("walk: each direction") {
    CHECK_EQ(walk({0, 0}, Direction::North, 3), Position{0, 3});
    CHECK_EQ(walk({0, 0}, Direction::East, 2), Position{2, 0});
    CHECK_EQ(walk({0, 0}, Direction::South, 1), Position{0, -1});
    CHECK_EQ(walk({0, 0}, Direction::West, 4), Position{-4, 0});
}

TEST("walk: from somewhere else, zero steps") {
    CHECK_EQ(walk({5, -2}, Direction::North, 2), Position{5, 0});
    CHECK_EQ(walk({5, -2}, Direction::West, 0), Position{5, -2});
}

TEST("follow: forward and turning") {
    CHECK_EQ(follow("FFRFF"), Position{2, 2});
    CHECK_EQ(follow("LF"), Position{-1, 0});
    CHECK_EQ(follow("RRFFF"), Position{0, -3});
}

TEST("follow: a full circle comes back") {
    CHECK_EQ(follow("FRFRFRF"), Position{0, 0});
    CHECK_EQ(follow("RRRRF"), Position{0, 1});
}

TEST("follow: no commands, other characters ignored") {
    CHECK_EQ(follow(""), Position{0, 0});
    CHECK_EQ(follow("F F x F!"), Position{0, 3});
}
