// === Lesson: Variadic templates ==============================================
//
// A variadic template takes any number of arguments of any types, like
// (...args) in JavaScript, except that every call is type-checked:
//
//     template <typename... Args>          // Args: a pack of types
//     void log_all(const Args &...args);   // args: a pack of parameters
//
//     log_all();                // Args is empty
//     log_all(1, "two", 3.0);   // Args is int, char[4], double
//
// A pack isn't a container: you can't index it or loop over it with for. You
// use it in three ways:
//
//     sizeof...(args)           // how many: a compile-time constant
//     other(args...)            // expansion: other(a1, a2, a3)
//     other(wrap(args)...)      // the pattern repeats: other(wrap(a1), wrap(a2), ...)
//
// A fold expression (C++17) combines a pack with a binary operator. The
// parentheses are part of the syntax:
//
//     (... op args)             // ((a1 op a2) op a3) ...    unary left fold
//     (args op ...)             // a1 op (a2 op (a3 ...))    unary right fold
//     (init op ... op args)     // ((init op a1) op a2) ...  binary fold, with a start
//
//     template <typename... Ts>
//     auto product(const Ts &...xs) { return (1 * ... * xs); }   // product() == 1
//
// The pack can sit inside a bigger expression, which is repeated for each
// element: (... && (args > 0)) is true when every argument is positive.
//
// An empty pack only works in a unary fold over &&, || or the comma operator:
// && gives true, || gives false. Any other operator needs the binary form,
// with a start value.
//
// The comma operator runs its operands in order, so a comma fold runs a
// statement once per argument, left to right, and can update local state:
//
//     template <typename... Args>
//     void print_numbered(const Args &...args) {
//         int n = 0;
//         ((std::cout << ++n << ": " << args << '\n'), ...);
//     }
//
//     print_numbered("ab", 3.5);   // prints "1: ab" then "2: 3.5"
//
// Read more: https://en.cppreference.com/w/cpp/language/fold
//            https://en.cppreference.com/w/cpp/language/pack
//
// === Exercise: Variadic templates ============================================
// Implement the five functions below with sizeof... and fold expressions.
//
// ./grade 15_templates/04_variadic

#include <cstddef>
#include <sstream>
#include <string>
#include <type_traits>

// Return the number of arguments passed.
// They can be of any types; only how many there are matters.
//
// Example:
//   count_args() == 0
//   count_args(42) == 1
//   count_args(1, "two", 3.0) == 3
template <typename... Args>
std::size_t count_args(const Args &...args) {
    throw "TODO";
}

// Return the sum of one or more arguments.
// The return type is whatever type all the arguments can convert to.
//
// Example:
//   sum_all(1, 2, 3) == 6
//   sum_all(5) == 5
//   sum_all(1, 2.5) == 3.5   // an int and a double give a double
//   sum_all(std::string("ab"), std::string("cd"), std::string("e")) == "abcde"
//
// There's always at least one argument, so a fold needs no start value.
template <typename... Args>
std::common_type_t<Args...> sum_all(const Args &...args) {
    throw "TODO";
}

// Return true if every argument is true (or non-zero).
// With no arguments, return true.
//
// Example:
//   all_true(true, true, true) == true
//   all_true(true, false, true) == false
//   all_true(1, 2, 3) == true
//   all_true(1, 0) == false
//   all_true() == true
//
// An empty && fold gives true, which matches "nothing failed".
template <typename... Args>
bool all_true(const Args &...args) {
    throw "TODO";
}

// Return true if any of the other arguments equals target.
// With nothing to compare against, return false.
//
// Example:
//   any_equal(3, 1, 2, 3) == true
//   any_equal(9, 1, 2, 3) == false
//   any_equal(std::string("b"), "a", "b") == true
//   any_equal(5) == false
//
// The first argument is the target; only the rest are compared with it.
template <typename T, typename... Args>
bool any_equal(const T &target, const Args &...args) {
    throw "TODO";
}

// Return every argument printed with <<, separated by separator.
// No separator goes before the first argument or after the last.
// With no arguments, return "".
//
// Example:
//   join_all(", ", 1, "two", 3.5) == "1, two, 3.5"
//   join_all("/", "usr", "local", "bin") == "usr/local/bin"
//   join_all("-", 'x') == "x"
//   join_all("-") == ""
//
// A std::ostringstream lets << build the text for any mix of types.
template <typename... Args>
std::string join_all(const std::string &separator, const Args &...args) {
    throw "TODO";
}
