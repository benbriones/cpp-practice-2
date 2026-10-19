// Punctuation handling for textutils.hpp. The instructions are in textutils.hpp.

#include <cctype>

#include "textutils.hpp"

// Helper: is c punctuation?
bool matches(char c) {
    return std::ispunct(static_cast<unsigned char>(c)) != 0;
}

std::string strip_punctuation(std::string_view text) {
    std::string result;
    for (char c : text) {
        if (!matches(c)) result += c;
    }
    return result;
}

int count_punctuation(std::string_view text) {
    int count = 0;
    for (char c : text) {
        if (matches(c)) ++count;
    }
    return count;
}
