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
