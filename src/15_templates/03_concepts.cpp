// === Lesson: Concepts and if constexpr =======================================
//
// A plain template accepts any type, and a bad one fails somewhere inside the
// body with a long error. A concept is a named compile-time yes/no question
// about a type. Constrain a template with one, and a call with the wrong type
// is rejected at the call site, with an error that names the unmet concept.
//
// <concepts> has the common ones: std::integral (bool and char count),
// std::floating_point, std::same_as<U>, std::convertible_to<U>,
// std::equality_comparable, std::totally_ordered (has <, <=, >, >=, ==, !=).
// Three ways to write a constraint:
//
//     template <std::floating_point T> T half(T x) { return x / 2; }
//     template <typename T> requires std::floating_point<T> T half(T x) { ... }
//     auto half(std::floating_point auto x) { return x / 2; }
//
// Your own concept is built from a requires-expression: expressions that must
// compile, optionally with a constraint on what they return. They're checked,
// never run:
//
//     template <typename T>
//     concept Named = requires(const T& t) {
//         t.id();                                             // must compile
//         { t.name() } -> std::convertible_to<std::string>;   // and give text
//     };
//
//     template <Named T> void greet(const T& thing);
//     static_assert(Named<Person>);   // a concept is also a bool expression
//
// The parameter is const T&, so t.id() and t.name() must work on a const
// object: a non-const name() member doesn't satisfy Named.
//
// if constexpr picks a branch at compile time. The branches not taken aren't
// compiled for that T, so each may use operations only some types have. A
// plain `if` would have to compile every branch for every T:
//
//     template <typename T>
//     std::string to_text(const T& value) {
//         if constexpr (std::is_same_v<T, std::string>) {
//             return value;
//         } else if constexpr (std::is_arithmetic_v<T>) {
//             return std::to_string(value);   // wouldn't compile for a std::string
//         } else {
//             return "?";
//         }
//     }
//
// Conditions can be concepts (std::integral<T>) or type traits from
// <type_traits> such as std::is_same_v<T, U> and std::is_pointer_v<T>. The
// first true branch wins, so put special cases before general ones.
//
// Read more: https://en.cppreference.com/w/cpp/language/constraints
//            https://www.learncpp.com/cpp-tutorial/constexpr-if-statements/
//
// === Exercise: Concepts and if constexpr =====================================
// Constrain each template as its comment asks, then write the bodies. The tests
// check both that good calls work and that bad ones don't compile.
//
// ./grade 15_templates/03_concepts

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// Return the greatest common divisor of a and b.
// The result is never negative, even when a or b is.
// Constrain T so only integer types are accepted: gcd(1.5, 2.5) must not compile.
//
// Example:
//   gcd(12, 18) == 6
//   gcd(-12, 18) == 6
//   gcd(0, 5) == 5
//   gcd(48u, 36u) == 12u
//
// With a constraint, a bad call is rejected at the call site, not inside the body.
template <typename T>
T gcd(T a, T b) {
    throw "TODO";
}

// Return value limited to [low, high]: low if it's below, high if it's above.
// Constrain T with std::totally_ordered, so it works for numbers and strings
// but not for types that can't be compared with <.
//
// Example:
//   clamp_to(5, 0, 10) == 5
//   clamp_to(-3, 0, 10) == 0
//   clamp_to(42, 0, 10) == 10
//   clamp_to(std::string("melon"), std::string("b"), std::string("k")) == "k"
//
// Strings compare alphabetically, so "melon" comes after "k" and clamps down to it.
template <typename T>
T clamp_to(const T& value, const T& low, const T& high) {
    throw "TODO";
}

// Replace `true` with a requires-expression.
// T must have a const member function area() whose result converts to double.
//
// Example:
//   struct Square { double side; double area() const { return side * side; } };
//   HasArea<Square> is true
//   HasArea<int> is false: int has no area()
//   HasArea<Fancy> is false when Fancy::area() returns a std::string
//
// Check area() on a const T&, so a non-const area() doesn't count.
template <typename T>
concept HasArea = true;

// Return the total area of a vector of shapes, adding up each shape's area().
// It works for any type that satisfies HasArea. An empty vector gives 0.0.
//
// Example:
//   std::vector<Square> squares{{2}, {3}};   // areas 4 and 9
//   total_area(squares) is 13.0
//   total_area(std::vector<Square>{}) is 0.0
//
// A vector of a type without a numeric area() is rejected at the call.
template <HasArea T>
double total_area(const std::vector<T>& shapes) {
    throw "TODO";
}

// Return a word naming T's category, decided at compile time:
//   "boolean" for bool (careful: bool counts as an integral type),
//   "integer" for other integer types, char included,
//   "decimal" for floating-point types,
//   "text"    for std::string, std::string_view and const char*,
//   "other"   for everything else.
//
// Example:
//   type_category<bool>() is "boolean"
//   type_category<char>() is "integer"
//   type_category<double>() is "decimal"
//   type_category<const char*>() is "text"
//   type_category<int*>() is "other"
//
// The first true branch wins, so check bool before the general integer case.
template <typename T>
std::string type_category() {
    throw "TODO";
}
