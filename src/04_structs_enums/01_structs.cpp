// Exercise: Structs
// A struct groups related values into one type. Its members are public, and
// you can initialise them by position or, since C++20, by name:
//
//   Point p{3.0, 4.0};    Point q{.x = 3.0, .y = 4.0};    p.x += 1;
//
// Small structs like Point are cheap to pass by value; pass bigger ones by
// const&. Coordinates work like a screen: x grows to the right, y grows DOWN,
// and a Rect is its top-left corner plus a width and height.
//
// Grade: grade 04_structs_enums/01_structs

#include <cmath>
#include <vector>

struct Point {
    double x{};
    double y{};
};

struct Rect {
    Point top_left;
    double width{};
    double height{};
};

// Straight-line distance between a and b. (std::sqrt or std::hypot, from <cmath>)
double distance(Point a, Point b) {
    throw "TODO";
}

// The point halfway between a and b.
Point midpoint(Point a, Point b) {
    throw "TODO";
}

double area(const Rect& r) {
    throw "TODO";
}

// True if p lies inside r or exactly on its edge.
bool contains(const Rect& r, Point p) {
    throw "TODO";
}

// The smallest Rect that contains every point. points is never empty.
Rect bounding_box(const std::vector<Point>& points) {
    throw "TODO";
}
