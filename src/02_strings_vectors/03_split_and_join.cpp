// === Lesson: Searching and slicing strings ===================================
//
// s.find(x) returns the index where x (a char or a string) first appears, or
// std::string::npos if it doesn't appear. s.find(x, start) begins searching at
// index start, and s.rfind(x) searches backwards from the end.
//
// npos is the largest std::size_t value, so keep positions in std::size_t (or
// auto) and compare them with npos, never with -1:
//
//     std::size_t at = email.find('@');
//     if (at == std::string::npos) { ... }    // no '@' in it
//
// s.substr(pos, count) copies up to count characters starting at pos. Leave
// out count to take everything to the end. pos == s.size() gives "", and
// pos > s.size() throws std::out_of_range.
//
//     std::string extension(const std::string& filename) {
//         std::size_t dot = filename.rfind('.');
//         if (dot == std::string::npos) {
//             return "";
//         }
//         return filename.substr(dot + 1);    // extension("a.tar.gz") == "gz"
//     }
//
// To visit every match, search again from just past the previous one:
//
//     int count_word(const std::string& text, const std::string& word) {
//         int count = 0;
//         std::size_t pos = text.find(word);
//         while (pos != std::string::npos) {
//             ++count;
//             pos = text.find(word, pos + word.size());
//         }
//         return count;
//     }
//
// Searching for any of several characters: s.find_first_of(chars) finds the
// first character that is in chars, and s.find_first_not_of(chars) the first
// that isn't. find_last_of and find_last_not_of search from the end.
//
// Choosing a parameter type: take `const std::string&` when you only read the
// string, and `std::string` by value when you need your own copy to change.
// The caller's string is untouched either way:
//
//     std::string shout(std::string text) {    // text is a copy
//         text += '!';
//         return text;
//     }
//
// To change characters in place, iterate by reference: for (char& c : text).
//
// Read more: https://en.cppreference.com/w/cpp/string/basic_string/find
//            https://en.cppreference.com/w/cpp/string/basic_string/substr
//
// === Exercise: Split, join, trim =============================================
// Small string utilities you'll reuse all the time. C++20's standard library
// has no split or trim, so people write their own.
//
// ./grade 02_strings_vectors/03_split_and_join

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

// Split on every delimiter. Empty fields are kept:
// split("a,b,,c", ',') == {"a", "b", "", "c"}. An empty string gives {}.
std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> split_values{};
    std::size_t pos = 0;
    while (pos != std::string::npos) {
        std::size_t del_pos = text.find(delimiter, pos);
        std::string vals = text.substr(0, del_pos);
        split_values.push_back(vals);
        pos = del_pos + 1;
    }
}

// The reverse of split: join({"a", "b", "c"}, ", ") == "a, b, c".
std::string join(const std::vector<std::string>& parts, const std::string& separator) {
    throw "TODO";
}

// Remove leading and trailing whitespace (spaces, tabs, newlines).
std::string trim(const std::string& text) { throw "TODO"; }

// Upper-case copy of text. The parameter is taken by value on purpose: you
// need a copy anyway, so modify the parameter and return it.
std::string to_upper(std::string text) { throw "TODO"; }
