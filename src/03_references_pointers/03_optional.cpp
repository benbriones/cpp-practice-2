// === Lesson: std::optional ===================================================
//
// std::optional<T> (from <optional>) holds either a T or nothing. It's how a
// function says "there may be no answer" without a magic value like -1 and
// without a pointer. It's like `number | undefined` in TypeScript, except that
// nothing forces you to check before you use the value.
//
//     std::optional<int> day_number(const std::string& name) {
//         if (name == "Mon") return 1;    // a T converts to an optional holding it
//         if (name == "Tue") return 2;
//         return std::nullopt;            // the empty optional
//     }
//
// Using one:
//
//     std::optional<int> d = day_number(input);
//     if (d) { ... }             // or d.has_value(): true when it holds a value
//     int n = *d;                // the value; undefined behavior if d is empty
//     int m = d.value();         // the value; throws std::bad_optional_access if empty
//     int k = d.value_or(0);     // the value, or 0 if d is empty
//     if (d == 2) { ... }        // compares the value; false when d is empty
//
// The empty state is std::nullopt (`return {};` works too). An optional stores
// its value inside itself, so there's no allocation and nothing to dangle.
//
// Sizes and indexes use std::size_t (from <cstddef>), an unsigned type, so
// std::optional<std::size_t> is the natural "maybe an index".
//
// Parsing numbers by hand. The characters '0' to '9' have consecutive codes, so
// c - '0' turns a digit character into its value: '7' - '0' == 7. Check that a
// character is a digit first with std::isdigit from <cctype>, passing it as an
// unsigned char: std::isdigit(static_cast<unsigned char>(c)).
//
// Detecting overflow. Check before the operation; afterwards it's already
// undefined behavior. For non-negative a and b, a + b overflows exactly when
// a > std::numeric_limits<int>::max() - b (from <limits>). The same idea works
// for other operations: rearrange the test so nothing in it can overflow.
//
// int's range is lopsided: it reaches down to -2'147'483'648 but only up to
// 2'147'483'647, so the most negative int has no positive counterpart.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdoptional/
//
// === Exercise: std::optional =================================================
// Implement the four functions below.
//
// ./grade 03_references_pointers/03_optional

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

// Parse a whole number: an optional '+' or '-', then one or more digits, and
// nothing else (no spaces, no decimal point). Return std::nullopt for anything
// else, including numbers outside the range of int. Don't use std::stoi:
// build the value digit by digit, and stop before anything overflows.
std::optional<int> parse_int(const std::string& text) {
    throw "TODO";
}

// Index of the first element equal to target, or std::nullopt.
std::optional<std::size_t> find_index(const std::vector<std::string>& items,
                                      const std::string& target) {
    throw "TODO";
}

// The first negative number, or std::nullopt if there are none.
// (No sentinel value could work here: every int is a possible answer.)
std::optional<int> first_negative(const std::vector<int>& values) {
    throw "TODO";
}

// The average, or std::nullopt for an empty vector.
std::optional<double> average(const std::vector<int>& values) {
    throw "TODO";
}
