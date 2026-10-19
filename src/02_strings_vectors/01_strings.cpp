// === Lesson: std::string =====================================================
//
// std::string (from <string>) is a growable sequence of chars. Unlike strings
// in JavaScript or Python it's mutable, and assigning it or passing it by value
// makes a full copy:
//
//     std::string s = "hello";
//     s[0] = 'j';                 // "jello"
//     s += " world";              // append a string...
//     s += '!';                   // ...or a single char
//     std::string t = s;          // an independent copy
//
// 'a' (single quotes) is a char; "a" (double quotes) is a string literal.
// c == "a" doesn't compile when c is a char, so mind the quotes.
//
// Useful members: s.size() (or s.length()), s.empty(), s.front(), s.back(),
// s.push_back(c), s.pop_back(). ==, != and < compare contents. s[i] doesn't
// check bounds: reading outside the string is undefined behavior.
//
// Visit each character with a range-for, or with an index when you need the
// position. Indexes are std::size_t, the unsigned type that size() returns:
//
//     for (char c : s) { ... }
//     for (std::size_t i = 0; i < s.size(); ++i) { ... s[i] ... }
//
// Unsigned values can't go below zero, so counting down needs care. This loop
// never ends: i >= 0 is always true, and --i at 0 wraps around to a huge number.
//
//     for (std::size_t i = s.size() - 1; i >= 0; --i)    // broken
//
// Counting down safely: loop while i > 0 and read s[i - 1].
//
// Character tests and conversions live in <cctype>: std::isalpha, std::isdigit,
// std::isspace, std::isupper, std::tolower, std::toupper. Pass them an unsigned
// char (a negative value is undefined behavior), and cast toupper's int result
// back to char:
//
//     std::string without_digits(const std::string& text) {
//         std::string result;
//         for (char c : text) {
//             if (!std::isdigit(static_cast<unsigned char>(c))) {
//                 result += c;
//             }
//         }
//         return result;
//     }
//
//     unsigned char q = 'q';
//     char upper = static_cast<char>(std::toupper(q));    // 'Q'
//
// A `const std::string&` parameter reads the caller's string without copying
// it, and can't change it. References get their own module next.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/
//            https://www.learncpp.com/cpp-tutorial/chars/
//
// === Exercise: std::string basics ============================================
// Implement the four functions below.
//
// ./grade 02_strings_vectors/01_strings

#include <cctype>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>

// How many times c appears in text.
int count_char(const std::string& text, char c) {
    int count = 0;
    for (std::size_t i = 0; i < text.size(); i++) {
        if (text[i] == c) count++;
    }

    return count;
}

// text backwards: reverse_string("abc") == "cba".
std::string reverse_string(const std::string& text) {
    std::string s = "";
    int textSize = text.size();

    for (int i = textSize - 1; i >= 0; i--) {
        s.push_back(text[i]);
    }

    return s;
}

// True if text reads the same both ways, ignoring case and anything that
// isn't a letter: "A man, a plan, a canal: Panama!" is a palindrome.
bool is_palindrome(const std::string& text) {
    std::string cleaned;

    // Get rid of any upper case letters and spaces
    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            cleaned += std::tolower(static_cast<unsigned char>(c));
        }
    }

    std::cout << "cleaned: " << cleaned << '\n';

    int left = 0;
    int right = cleaned.size() - 1;

    while (left < right) {
        if (cleaned[left] != cleaned[right]) return false;
        left++;
        right--;
    }

    // cleaned:racecar
    // cleaned:abba
    // cleaned:abca
    return true;
}

// The upper-case first letter of each word: initials("ada king lovelace") == "AKL".
// Words are separated by one or more spaces.
std::string initials(const std::string& full_name) {
    std::string initials;

    for (std::size_t i = 0; i < full_name.size(); i++) {

        // First letter
        if (i == 0) {
            char cap = std::toupper(full_name[i]);
            initials += cap;
            continue;
        }

        // If space before letter 
        if (full_name[i-1] == ' ') {
            char cap = std::toupper(full_name[i]);
            initials += cap;
        }
    }

    return initials;
}
