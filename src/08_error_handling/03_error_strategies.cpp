// === Lesson: Choosing how to report failure ==================================
//
// C++ code reports "this didn't work" in several ways, and you'll meet all of
// them. Each suits a different situation:
//
//   bool + out-parameter   older, C-style code; the bool is easy to ignore.
//   std::optional<T>       failure is ordinary and the caller needs no details.
//   exception              failure is rare, mustn't be ignored, or is handled far away.
//
// Here is one lookup, seen from the caller's side in each style:
//
//     int id;
//     if (try_find_id(ids, "ada", id)) use(id);         // bool + out-parameter
//
//     if (auto found = find_id(ids, "ada")) use(*found); // std::optional<int>
//     int id_or_zero = find_id(ids, "ada").value_or(0);
//
//     use(find_id_or_throw(ids, "ada"));                 // throws if missing
//
// Don't write the logic three times. Write it once, in the style that fits it
// best, and make the others thin wrappers around it:
//
//     std::optional<int> find_id(const std::map<std::string, int>& ids,
//                                const std::string& name) {
//         auto it = ids.find(name);
//         if (it == ids.end()) return std::nullopt;
//         return it->second;
//     }
//
//     int find_id_or_throw(const std::map<std::string, int>& ids,
//                          const std::string& name) {
//         if (auto id = find_id(ids, name)) return *id;
//         throw std::invalid_argument("no user named " + name);
//     }
//
// An out-parameter function should leave its out-parameter alone when it fails,
// so a caller's earlier value survives.
//
// Parsing numbers: std::stoi skips leading spaces, accepts a sign, stops quietly
// at trailing junk, and throws when the value doesn't fit in an int. A strict
// parser checks the characters itself before trusting it. std::from_chars (from
// <charconv>) is stricter and never throws: it skips no spaces, rejects a '+',
// and returns an error code plus a pointer to where it stopped reading.
//
// C++23 adds std::expected<T, E>, which holds either a value or an error
// describing what went wrong. In C++20, std::optional is the closest fit.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdoptional/
//            https://en.cppreference.com/w/cpp/utility/from_chars
//
// === Exercise: Three ways to report failure ==================================
// The same parser written three ways. A valid age is 1 to 3 digits (nothing else,
// no sign, no spaces) with a value from 0 to 150.
//
// Write the parsing logic once, then build the other two versions on top of it.
//
// ./grade 08_error_handling/03_error_strategies

#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// Parse text as an age and report whether it worked.
// On success, store the age in out and return true.
// On failure, return false and leave out untouched.
//
// Example:
//   int age = 33;
//   try_parse_age("nope", age) is false, and age is still 33
//   try_parse_age("007", age) is true, and age is now 7
//   try_parse_age("151", age) is false, and age is still 7
//
// Leaving out alone on failure means the caller's earlier value survives.
bool try_parse_age(std::string_view text, int& out) {
    throw "TODO";
}

// Return the age parsed from text, or std::nullopt if text isn't a valid age.
//
// Example:
//   parse_age("42") is 42
//   parse_age("0") is 0
//   parse_age("151") is std::nullopt
//   parse_age("") is std::nullopt
std::optional<int> parse_age(std::string_view text) {
    throw "TODO";
}

// Return the age parsed from text.
// Throw std::invalid_argument("invalid age: <text>") if text isn't a valid age.
//
// Example:
//   parse_age_or_throw("150") is 150
//   parse_age_or_throw("151") throws std::invalid_argument
//   parse_age_or_throw("12x") throws, and what() is "invalid age: 12x"
int parse_age_or_throw(std::string_view text) {
    throw "TODO";
}

// Return the average of the valid ages in texts.
// Skip texts that aren't valid ages.
// Return std::nullopt if none are valid, including when texts is empty.
//
// Example:
//   average_age({"20", "30"}) is 25.0
//   average_age({"20", "abc", "31", "500"}) is 25.5   // (20 + 31) / 2
//   average_age({"x", "-1"}) is std::nullopt
std::optional<double> average_age(const std::vector<std::string>& texts) {
    throw "TODO";
}
