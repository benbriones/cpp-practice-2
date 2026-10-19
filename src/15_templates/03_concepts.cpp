// Exercise: Concepts and if constexpr
// A concept states what a template needs from its types, so a bad call is
// rejected up front with a readable error instead of failing deep inside.
//
//     template <std::integral T> T half(T x);                 // a standard concept
//     template <typename T> requires std::floating_point<T> T root(T x);
//     template <typename T>
//     concept Named = requires(const T& t) { { t.name() } -> std::convertible_to<std::string>; };
//
// `if constexpr (condition)` picks a branch at compile time; the other branches
// aren't compiled for that type.
//
// Grade: grade 15_templates/03_concepts

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// Greatest common divisor, never negative: gcd(-12, 18) == 6, gcd(0, 5) == 5.
// Constrain T so only integer types are accepted (gcd(1.5, 2.5) must not compile).
template <typename T>
T gcd(T a, T b) {
    throw "TODO";
}

// value limited to [low, high]. Constrain T with std::totally_ordered, so it works
// for numbers and strings but not for types that can't be compared with <.
template <typename T>
T clamp_to(const T& value, const T& low, const T& high) {
    throw "TODO";
}

// Replace `true` with a requires-expression: T must have a const member function
// area() whose result converts to double.
template <typename T>
concept HasArea = true;

// Total area of a vector of shapes of any type that satisfies HasArea.
template <HasArea T>
double total_area(const std::vector<T>& shapes) {
    throw "TODO";
}

// Decide at compile time:
//   "boolean" for bool (careful: bool counts as an integral type),
//   "integer" for other integer types, char included,
//   "decimal" for floating-point types,
//   "text"    for std::string, std::string_view and const char*,
//   "other"   for everything else.
template <typename T>
std::string type_category() {
    throw "TODO";
}
