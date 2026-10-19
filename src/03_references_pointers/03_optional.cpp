// Exercise: std::optional
// std::optional<T> holds either a T or nothing (std::nullopt). It says
// "there may be no answer" more clearly than a magic value like -1 or a
// null pointer, and it works for answers where every value is legal.
//
//   std::optional<int> maybe = 42;     if (maybe) { use(*maybe); }
//   return std::nullopt;               maybe.value_or(0)
//
// Grade: grade 03_references_pointers/03_optional

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
