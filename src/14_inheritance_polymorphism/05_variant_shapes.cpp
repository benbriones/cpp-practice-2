// Challenge: Shapes without inheritance
// The shapes again, this time as plain structs held in a std::variant: a value
// that is exactly one of a fixed list of types. std::visit calls whichever
// function matches the type it currently holds.
//
// Inheritance fits an open set of types (anyone can add a new shape). A variant
// fits a closed set: the list of types is fixed, but adding a new operation is
// just a new function, and no heap allocation or pointers are needed.
//
// Grade: grade 14_inheritance_polymorphism/05_variant_shapes

#include <array>
#include <cmath>
#include <numbers>
#include <string>
#include <variant>
#include <vector>

struct Circle {
    double radius = 0;
};

struct Rectangle {
    double width = 0;
    double height = 0;
};

struct Triangle {
    double a = 0;
    double b = 0;
    double c = 0;
};

using Shape = std::variant<Circle, Rectangle, Triangle>;

// Bundles several lambdas into one callable, so std::visit can pick by type:
//   std::visit(overloaded{[](const Circle& c) { ... }, [](const Rectangle& r) { ... },
//                         [](const Triangle& t) { ... }}, shape);
template <class... Functions>
struct overloaded : Functions... {
    using Functions::operator()...;
};

// Triangle area by Heron's formula, as in 02_shapes.
double area(const Shape& shape) {
    throw "TODO";
}

double perimeter(const Shape& shape) {
    throw "TODO";
}

// "circle", "rectangle", or "triangle"
std::string name(const Shape& shape) {
    throw "TODO";
}

// A new shape of the same kind with every length multiplied by factor.
Shape scaled(const Shape& shape, double factor) {
    throw "TODO";
}

// How many shapes of each kind, in the order {circles, rectangles, triangles}.
// shape.index() tells you which alternative a variant holds (0, 1, or 2 here).
std::array<int, 3> count_kinds(const std::vector<Shape>& shapes) {
    throw "TODO";
}

// The total area of just the circles. std::get_if<Circle>(&shape) returns a
// pointer to the Circle, or nullptr if the shape holds something else.
double total_circle_area(const std::vector<Shape>& shapes) {
    throw "TODO";
}
