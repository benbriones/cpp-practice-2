#include "grader.hpp"
#include "04_structs_enums/01_structs.cpp"

TEST("distance: a 3-4-5 triangle") {
    CHECK_NEAR(distance({0, 0}, {3, 4}), 5.0);
    CHECK_NEAR(distance({3, 4}, {0, 0}), 5.0);
}

TEST("distance: same point, negative coordinates") {
    CHECK_NEAR(distance({2, 2}, {2, 2}), 0.0);
    CHECK_NEAR(distance({-1, -1}, {2, 3}), 5.0);
}

TEST("midpoint") {
    Point m = midpoint({0, 0}, {4, 2});
    CHECK_NEAR(m.x, 2.0);
    CHECK_NEAR(m.y, 1.0);
    m = midpoint({-3, 5}, {1, -5});
    CHECK_NEAR(m.x, -1.0);
    CHECK_NEAR(m.y, 0.0);
}

TEST("area") {
    CHECK_NEAR(area({.top_left = {1, 1}, .width = 3, .height = 4}), 12.0);
    CHECK_NEAR(area({.top_left = {0, 0}, .width = 0, .height = 5}), 0.0);
}

TEST("contains: points inside and outside") {
    const Rect r{.top_left = {0, 0}, .width = 10, .height = 5};
    CHECK_EQ(contains(r, {5, 2}), true);
    CHECK_EQ(contains(r, {11, 2}), false);
    CHECK_EQ(contains(r, {-1, 2}), false);
    CHECK_EQ(contains(r, {5, 6}), false);
    CHECK_EQ(contains(r, {5, -0.5}), false);
}

TEST("contains: edges and corners count as inside") {
    const Rect r{.top_left = {0, 0}, .width = 10, .height = 5};
    CHECK_EQ(contains(r, {0, 0}), true);
    CHECK_EQ(contains(r, {10, 5}), true);
    CHECK_EQ(contains(r, {10, 2}), true);
    CHECK_EQ(contains(r, {3, 5}), true);
}

TEST("contains: y grows downward from the top-left corner") {
    const Rect r{.top_left = {2, 3}, .width = 4, .height = 2};
    CHECK_EQ(contains(r, {4, 4}), true);
    CHECK_EQ(contains(r, {4, 2}), false);
    CHECK_EQ(contains(r, {4, 5.5}), false);
}

TEST("bounding_box: several points") {
    Rect box = bounding_box({{1, 5}, {4, 2}, {-2, 3}});
    CHECK_NEAR(box.top_left.x, -2.0);
    CHECK_NEAR(box.top_left.y, 2.0);
    CHECK_NEAR(box.width, 6.0);
    CHECK_NEAR(box.height, 3.0);
}

TEST("bounding_box: a single point") {
    Rect box = bounding_box({{7, -3}});
    CHECK_NEAR(box.top_left.x, 7.0);
    CHECK_NEAR(box.top_left.y, -3.0);
    CHECK_NEAR(box.width, 0.0);
    CHECK_NEAR(box.height, 0.0);
}
