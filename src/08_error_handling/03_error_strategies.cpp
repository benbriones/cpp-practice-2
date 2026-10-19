// Exercise: Three ways to report failure
// The same parser written three ways. A valid age is 1 to 3 digits (nothing else,
// no sign, no spaces) with a value from 0 to 150.
//
//   bool + out-parameter   C-style; common in older code, and the bool is easy to ignore.
//   std::optional          failure is ordinary and the caller needs no details.
//   exception              failure is rare, mustn't be ignored, or is handled far away.
//
// Write the parsing logic once, then build the other two versions on top of it.
//
// ./grade 08_error_handling/03_error_strategies

#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// On success, store the age in out and return true. On failure, return false and
// leave out untouched.
bool try_parse_age(std::string_view text, int& out) {
    throw "TODO";
}

// The age, or std::nullopt.
std::optional<int> parse_age(std::string_view text) {
    throw "TODO";
}

// The age, or throw std::invalid_argument("invalid age: <text>").
int parse_age_or_throw(std::string_view text) {
    throw "TODO";
}

// The average of the valid ages in texts (invalid ones are skipped), or
// std::nullopt if none are valid.
std::optional<double> average_age(const std::vector<std::string>& texts) {
    throw "TODO";
}
