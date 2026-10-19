#include "grader.hpp"
#include "16_multi_file_programs/01_split_into_files/geometry.hpp"
#include "16_multi_file_programs/01_split_into_files/geometry.hpp"  // twice on purpose

TEST("distance") {
    CHECK_NEAR(distance({0, 0}, {3, 4}), 5.0);
    CHECK_NEAR(distance({1, 1}, {1, 1}), 0.0);
}

TEST("circle_area") {
    CHECK_NEAR(circle_area(1), 3.14159265358979);
    CHECK_NEAR(circle_area(2), 12.5663706143592);
}

TEST("midpoint") {
    const Point middle = midpoint({0, 0}, {4, -2});
    CHECK_NEAR(middle.x, 2.0);
    CHECK_NEAR(middle.y, -1.0);
}

TEST("triangle_perimeter (defined in geometry.cpp)") {
    CHECK_NEAR(triangle_perimeter({0, 0}, {3, 0}, {3, 4}), 12.0);
}
