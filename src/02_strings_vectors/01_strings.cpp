// Exercise: std::string basics
// Implement the four functions below.
//
// A std::string works like an array of char: s.size(), s[i], s += 'x',
// s + other. Character helpers live in <cctype> (std::isalpha, std::toupper...);
// pass them static_cast<unsigned char>(c), not a plain char.
//
// `const std::string&` means "read this string without copying it".
// References get their own module next.
//
// ./grade 02_strings_vectors/01_strings

#include <cctype>
#include <string>

// How many times c appears in text.
int count_char(const std::string& text, char c) {
    throw "TODO";
}

// text backwards: reverse_string("abc") == "cba".
std::string reverse_string(const std::string& text) {
    throw "TODO";
}

// True if text reads the same both ways, ignoring case and anything that
// isn't a letter: "A man, a plan, a canal: Panama!" is a palindrome.
bool is_palindrome(const std::string& text) {
    throw "TODO";
}

// The upper-case first letter of each word: initials("ada king lovelace") == "AKL".
// Words are separated by one or more spaces.
std::string initials(const std::string& full_name) {
    throw "TODO";
}
