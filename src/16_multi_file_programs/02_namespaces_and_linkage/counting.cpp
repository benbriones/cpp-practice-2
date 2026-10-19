// Vowel counting for textutils.hpp. The instructions are in textutils.hpp.

#include <cctype>

#include "textutils.hpp"

// Helper: is c a vowel?
bool matches(char c) {
    switch (std::tolower(static_cast<unsigned char>(c))) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

int count_vowels(std::string_view text) {
    int count = 0;
    for (char c : text) {
        if (matches(c)) ++count;
    }
    return count;
}

int count_vowel_words(std::string_view text) {
    int count = 0;
    bool at_word_start = true;
    for (char c : text) {
        if (c == ' ') {
            at_word_start = true;
        } else {
            if (at_word_start && matches(c)) ++count;
            at_word_start = false;
        }
    }
    return count;
}
