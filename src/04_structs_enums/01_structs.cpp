// === Lesson: Structs =========================================================
//
// A struct groups named values into a new type. Its members are public, so it's
// C++'s plain record, like a TypeScript object type or a Python dataclass.
//
//     struct Size {
//         int width{};      // {} gives each member a default of 0
//         int height{};
//     };
//
// Give every member a default with {} or = value. Without one, `Size s;` leaves
// int and double members holding garbage.
//
// Creating one: by position, or by name with C++20 designated initializers.
// Names must appear in declaration order, and any you skip keep their default:
//
//     Size a{1920, 1080};
//     Size b{.width = 800, .height = 600};
//     Size c{.height = 50};             // width is 0
//     a.width += 10;                    // members are reached with .
//
// A struct is a value, not a handle. Assigning or passing one copies every
// member, unlike objects in JavaScript or Python:
//
//     Size d = a;
//     d.width = 0;                      // a is unchanged
//
// Structs nest, and the braces nest with them:
//
//     struct Window { Size size; std::string title; };
//     Window w{{640, 480}, "Editor"};
//     w.size.height = 400;
//
// A function can return a struct as a braced list of its members, in order:
//
//     Size doubled(Size s) { return {s.width * 2, s.height * 2}; }
//
// Pass small structs (a couple of numbers) by value and bigger ones by const&
// to avoid the copy. Structs don't get == for free: a == b doesn't compile
// unless the struct asks for it (module 13 shows how).
//
// std::min(a, b) and std::max(a, b), from <algorithm>, give the smaller or
// larger of two values of the same type.
//
// Read more: https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/
//            https://www.learncpp.com/cpp-tutorial/passing-and-returning-structs/
//
// === Exercise: Structs =======================================================
// Implement the five functions below. Coordinates work like a screen: x grows to
// the right, y grows downward, and a Rect is its top-left corner plus a width
// and height.
//
// ./grade 04_structs_enums/01_structs

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

// Return the straight-line distance between a and b.
// The order doesn't matter: distance(a, b) equals distance(b, a).
// std::sqrt or std::hypot, from <cmath>, will help.
//
// Example:
//   distance({0, 0}, {3, 4}) is 5.0
//   distance({-1, -1}, {2, 3}) is 5.0
//   distance({2, 2}, {2, 2}) is 0.0
double distance(Point a, Point b) {
    throw "TODO";
}

// Return the point halfway between a and b.
//
// Example:
//   midpoint({0, 0}, {4, 2}) is {2, 1}
//   midpoint({-3, 5}, {1, -5}) is {-1, 0}
Point midpoint(Point a, Point b) {
    throw "TODO";
}

double area(const Rect &r) {
    throw "TODO";
}

// Return true if p lies inside r or exactly on its edge.
// r spans x from top_left.x to top_left.x + width, and y from top_left.y
// down to top_left.y + height.
//
// Example:
//   r = {.top_left = {0, 0}, .width = 10, .height = 5}
//   contains(r, {5, 2}) is true
//   contains(r, {10, 5}) is true      // a corner counts as inside
//   contains(r, {11, 2}) is false
//   contains(r, {5, -0.5}) is false   // just above the top edge
bool contains(const Rect &r, Point p) {
    throw "TODO";
}

// Return the smallest Rect that contains every point.
// Its edges pass through the outermost points, which count as inside.
// A single point gives a Rect with width 0 and height 0.
// points is never empty.
//
// Example:
//   bounding_box({{1, 5}, {4, 2}, {-2, 3}})
//   // top_left is {-2, 2}, width is 6, height is 3
//   bounding_box({{7, -3}})
//   // top_left is {7, -3}, width and height are 0
Rect bounding_box(const std::vector<Point> &points) {
    throw "TODO";
}
