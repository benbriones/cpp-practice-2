// === Lesson: std::variant and std::visit =====================================
//
// A std::variant<A, B, C> holds exactly one value of one of the listed types,
// stored inside the variant itself (no heap allocation). It's C++'s tagged
// union, like a TypeScript union `A | B | C` that you switch on:
//
//     struct Click { int x = 0; int y = 0; };
//     struct Key { char ch = 0; };
//     using Event = std::variant<Click, Key>;
//
//     Event e = Key{'q'};               // holds a Key
//     e.index();                        // 1: Key's position in the list
//     std::holds_alternative<Key>(e);   // true
//     std::get<Key>(e).ch;              // 'q'
//     std::get<Click>(e);               // throws std::bad_variant_access
//     std::get_if<Click>(&e);           // a Click*, here nullptr: e holds a Key
//     e = Click{3, 4};                  // now it holds a Click
//
// std::visit calls a function with whatever the variant holds. Bundle one lambda
// per type with the `overloaded` helper below, and visit picks the match:
//
//     std::string describe(const Event& e) {
//         return std::visit(overloaded{
//             [](const Click& c) { return "click at " + std::to_string(c.x); },
//             [](const Key& k) { return std::string("key ") + k.ch; },
//         }, e);
//     }
//
// Leave a type out and it doesn't compile, so adding an alternative shows you
// every visit that needs updating.
//
// Every lambda in one visit must return the same type. When each would return
// its own struct, give them all an explicit return type, the variant itself:
//
//     [](const Click& c) -> Event { return Click{c.x + 1, c.y}; }
//
// A generic lambda, [](const auto& value) { ... }, handles every type with one
// body, when they all support what the body does.
//
// Inheritance or variant? Inheritance fits an open set of types: anyone can add
// a derived class. A variant fits a closed set: the types are fixed, but a new
// operation is just a new function, and values need no pointers or heap.
//
// Read more: https://en.cppreference.com/w/cpp/utility/variant
//            https://en.cppreference.com/w/cpp/utility/variant/visit2
//
// === Challenge: Shapes without inheritance ===================================
// The shapes again, this time as plain structs held in a std::variant.
//
// ./grade 14_inheritance_polymorphism/05_variant_shapes

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

// Return the shape's area.
// Circle: pi × radius × radius. Rectangle: width × height.
// Triangle area by Heron's formula, as in 02_shapes.
//
// Example:
//   area(Circle{2}) is 4 * pi
//   area(Rectangle{3, 4}) is 12
//   area(Triangle{3, 4, 5}) is 6
//
// std::visit with overloaded picks the formula for whichever kind the shape holds.
double area(const Shape& shape) {
    throw "TODO";
}

double perimeter(const Shape& shape) {
    throw "TODO";
}

// Return the shape's kind: "circle", "rectangle", or "triangle".
//
// Example:
//   name(Rectangle{1, 1}) is "rectangle"
std::string name(const Shape& shape) {
    throw "TODO";
}

// Return a new shape of the same kind with every length multiplied by factor.
// The original shape doesn't change.
//
// Example:
//   scaled(Circle{2}, 1.5) is Circle{3}
//   scaled(Rectangle{1, 2}, 2) is Rectangle{2, 4}
//   scaled(Triangle{3, 4, 5}, 0.5) is Triangle{1.5, 2, 2.5}
//
// Area grows with the square of the factor: area(scaled(Rectangle{3, 4}, 3)) is 108.
Shape scaled(const Shape& shape, double factor) {
    throw "TODO";
}

// Return how many shapes of each kind, in the order {circles, rectangles, triangles}.
// shape.index() tells you which alternative a variant holds (0, 1, or 2 here).
//
// Example:
//   count_kinds({Circle{1}, Triangle{3, 4, 5}, Circle{2}, Rectangle{1, 1}, Circle{3}})
//   returns {3, 1, 1}
//   count_kinds({}) returns {0, 0, 0}
std::array<int, 3> count_kinds(const std::vector<Shape>& shapes) {
    throw "TODO";
}

// Return the total area of just the circles; every other shape is skipped.
// std::get_if<Circle>(&shape) returns a pointer to the Circle,
// or nullptr if the shape holds something else.
//
// Example:
//   total_circle_area({Circle{1}, Rectangle{10, 10}, Circle{2}}) is 5 * pi   // pi + 4 * pi
//   total_circle_area({Rectangle{1, 2}, Triangle{3, 4, 5}}) is 0
double total_circle_area(const std::vector<Shape>& shapes) {
    throw "TODO";
}
