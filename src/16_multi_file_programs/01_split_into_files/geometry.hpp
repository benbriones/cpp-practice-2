// Exercise: Split a header from its source file
// This folder doesn't build yet. Every function below is *defined* in this
// header, and two files include it (geometry.cpp and the tests), so each
// function gets compiled twice. The tests also include this header twice.
//
// Fix it the standard way, running grade after each step to see the next error:
//   1. Add #pragma once at the top of this file, so a repeated #include is skipped.
//   2. Leave only declarations here, like the one for triangle_perimeter:
//          double circle_area(double radius);
//   3. Move the function bodies into geometry.cpp.
//
// (Marking each function `inline` would also link. That's how header-only
// libraries work, but practise the header/source split here.)
//
// Grade: grade 16_multi_file_programs/01_split_into_files

#include <cmath>

struct Point {
    double x{};
    double y{};
};

double distance(Point a, Point b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}

double circle_area(double radius) {
    return 3.14159265358979 * radius * radius;
}

Point midpoint(Point a, Point b) {
    return {(a.x + b.x) / 2, (a.y + b.y) / 2};
}

double triangle_perimeter(Point a, Point b, Point c);
