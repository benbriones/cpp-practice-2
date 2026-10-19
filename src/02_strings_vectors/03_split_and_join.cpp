// Exercise: Split, join, trim
// Small string utilities you'll reuse all the time. C++20's standard library
// has no split or trim, so people write their own.
//
// Useful: s.find(c, start) gives an index or std::string::npos if not found;
// s.substr(start, length); s.empty().
//
// Grade: grade 02_strings_vectors/03_split_and_join

#include <cctype>
#include <string>
#include <vector>

// Split on every delimiter. Empty fields are kept:
// split("a,b,,c", ',') == {"a", "b", "", "c"}. An empty string gives {}.
std::vector<std::string> split(const std::string& text, char delimiter) {
    throw "TODO";
}

// The reverse of split: join({"a", "b", "c"}, ", ") == "a, b, c".
std::string join(const std::vector<std::string>& parts, const std::string& separator) {
    throw "TODO";
}

// Remove leading and trailing whitespace (spaces, tabs, newlines).
std::string trim(const std::string& text) {
    throw "TODO";
}

// Upper-case copy of text. The parameter is taken by value on purpose: you
// need a copy anyway, so modify the parameter and return it.
std::string to_upper(std::string text) {
    throw "TODO";
}
