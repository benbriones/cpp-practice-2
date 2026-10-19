// Exercise: Variadic templates
// A parameter pack takes any number of arguments, of any types:
//
//     template <typename... Args>
//     void f(const Args&... args);
//
// sizeof...(args) counts them. A fold expression applies an operator across them:
//     (... + args)           is ((a1 + a2) + a3) + ...
//     (... && args)          is true for an empty pack
//     ((out << args), ...)   runs `out << arg` for each argument, in order
//
// ./grade 15_templates/04_variadic

#include <cstddef>
#include <sstream>
#include <string>
#include <type_traits>

// Number of arguments: count_args() == 0, count_args(1, "two", 3.0) == 3.
template <typename... Args>
std::size_t count_args(const Args&... args) {
    throw "TODO";
}

// Sum of one or more arguments: sum_all(1, 2, 3) == 6, sum_all(1, 2.5) == 3.5.
// The return type is whatever type all the arguments can convert to.
template <typename... Args>
std::common_type_t<Args...> sum_all(const Args&... args) {
    throw "TODO";
}

// True if every argument is true (or non-zero). all_true() == true.
template <typename... Args>
bool all_true(const Args&... args) {
    throw "TODO";
}

// True if any of the other arguments equals target: any_equal(3, 1, 2, 3) == true.
template <typename T, typename... Args>
bool any_equal(const T& target, const Args&... args) {
    throw "TODO";
}

// Every argument printed with <<, separated by separator:
// join_all(", ", 1, "two", 3.5) == "1, two, 3.5", join_all("-") == "".
template <typename... Args>
std::string join_all(const std::string& separator, const Args&... args) {
    throw "TODO";
}
