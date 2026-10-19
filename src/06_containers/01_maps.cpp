// Exercise: std::map
// A std::map<Key, Value> holds key/value pairs, kept sorted by key.
//     counts["apple"] += 1;          // [] inserts a missing key with value 0 first
//     counts.contains("pear");       // look up without inserting (C++20)
//     for (const auto& [word, count] : counts) { ... }   // visits keys in sorted order
// `using` gives a long type a short name.
//
// ./grade 06_containers/01_maps

#include <cctype>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

using WordCounts = std::map<std::string, int>;

// Count each word. Words are runs of letters (a–z, A–Z); everything else separates them.
// Store words in lower case: "The cat, the HAT." gives {"cat": 1, "hat": 1, "the": 2}.
WordCounts word_counts(const std::string& text) {
    throw "TODO";
}

// The word with the highest count; ties go to the alphabetically first word.
// Return "" for an empty map.
std::string most_common(const WordCounts& counts) {
    throw "TODO";
}

// Add b's counts into a and return the result: {"a": 1} merged with {"a": 2, "b": 1}
// gives {"a": 3, "b": 1}.
WordCounts merge(WordCounts a, const WordCounts& b) {
    throw "TODO";
}

// Group words by length, each group in input order:
// group_by_length({"to", "be", "or", "not"}) == {2: {"to", "be", "or"}, 3: {"not"}}
std::map<std::size_t, std::vector<std::string>> group_by_length(
    const std::vector<std::string>& words) {
    throw "TODO";
}
