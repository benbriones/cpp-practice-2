// Exercise: std::string_view
// A std::string_view is a read-only window onto characters stored somewhere
// else: a std::string, a string literal, part of either. Creating one copies
// nothing, and neither does sv.substr(). It doesn't own the characters, so
// whatever it views must outlive it.
//
// Useful: sv.size(), sv[i], sv.substr(pos, len), sv.find(c),
// sv.remove_prefix(n), sv.remove_suffix(n), sv.starts_with(other)
//
// Each function below must return a view into its input, never a copy.
//
// ./grade 03_references_pointers/04_string_view

#include <cctype>
#include <cstddef>
#include <string_view>

// Number of words: runs of non-whitespace characters.
// count_words("  hi \t there\n") == 2
std::size_t count_words(std::string_view text) {
    throw "TODO";
}

// The first word of text, skipping leading whitespace. Empty if there is none.
// first_word("  hello world") == "hello"
std::string_view first_word(std::string_view text) {
    throw "TODO";
}

// text without its leading and trailing whitespace.
std::string_view trim_view(std::string_view text) {
    throw "TODO";
}

// If text starts with prefix, the rest of text; otherwise text unchanged.
// strip_prefix("unhappy", "un") == "happy"
std::string_view strip_prefix(std::string_view text, std::string_view prefix) {
    throw "TODO";
}
