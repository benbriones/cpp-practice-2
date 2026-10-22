// === Lesson: std::map ========================================================
//
// std::map<Key, Value> stores key/value pairs with unique keys, like a Python
// dict or a JS Map, with one difference: it's kept sorted by key (it's a
// balanced tree), so lookups are O(log n) and loops visit the keys in order.
//
//     #include <map>
//
//     std::map<std::string, int> stock{{"pear", 4}, {"apple", 10}};
//
//     stock["kiwi"] = 7;                    // insert, or overwrite if present
//     stock["plum"] += 3;                   // a missing key starts at int{}, i.e. 0
//     stock.erase("pear");
//
//     if (stock.contains("fig")) { ... }    // check without inserting (C++20)
//     int apples = stock.at("apple");       // throws std::out_of_range if missing
//
//     auto it = stock.find("kiwi");         // one lookup, then use the result
//     if (it != stock.end()) {              // end() means "not found"
//         it->second -= 1;                  // it->first is the key
//     }
//
//     for (const auto& [fruit, count] : stock) {   // apple, kiwi, plum
//         std::cout << fruit << ": " << count << '\n';
//     }
//
// operator[] creates the entry when the key is missing, using the value type's
// default: 0 for numbers, "" for strings, an empty vector for vectors. That
// keeps counting and grouping code short, but it also means a lookup can
// insert by accident:
//
//     if (stock["fig"] > 0) { ... }   // adds "fig" with 0 as a side effect
//
// For the same reason, [] doesn't compile on a const map. To read from a const
// map, use find(), at() or contains().
//
// Each element is a std::pair<const Key, Value>. Keys can't change in place
// (that would break the sorting), but values can, through a reference:
//
//     for (auto& [fruit, count] : stock) count *= 2;
//
// `using` gives a long type a short name:  using Stock = std::map<std::string, int>;
//
// Passing a map: const Stock& to read it, and Stock (by value) when the function
// is going to change its own copy anyway.
//
// Read more: https://en.cppreference.com/w/cpp/container/map
//
// === Exercise: std::map ======================================================
// Implement the four functions below.
//
// ./grade 06_containers/01_maps

#include <cctype>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

using WordCounts = std::map<std::string, int>;

// Count how many times each word appears in text.
// Words are runs of letters (a–z, A–Z); everything else separates them.
// Store words in lower case, so "The" and "the" count as the same word.
//
// Example:
//   word_counts("The cat, the HAT.") is {"cat": 1, "hat": 1, "the": 2}
//   word_counts("x1y--z  x") is {"x": 2, "y": 1, "z": 1}
//   word_counts(" 123 !? ") is {}
//
// The map keeps its keys sorted, so the words come out in alphabetical order.
WordCounts word_counts(const std::string& text) {
    throw "TODO";
}

// Return the word with the highest count.
// If several words tie for the highest count, return the alphabetically first one.
// Return "" for an empty map.
//
// Example:
//   most_common({"apple": 2, "pear": 5, "plum": 1}) is "pear"
//   most_common({"zebra": 3, "apple": 3, "mango": 1}) is "apple"   // a tie
//   most_common({}) is ""
//
// counts is const, so read it with a loop, find() or at(); [] won't compile.
std::string most_common(const WordCounts& counts) {
    throw "TODO";
}

// Add b's counts into a and return the result.
// A word in both maps gets the sum of its counts; a word in only one keeps its count.
//
// Example:
//   merge({"a": 1}, {"a": 2, "b": 1}) is {"a": 3, "b": 1}
//   merge({}, {"x": 4}) is {"x": 4}
//
// a is taken by value, so the function changes its own copy and returns it.
WordCounts merge(WordCounts a, const WordCounts& b) {
    throw "TODO";
}

// Group words by length.
// Each key is a length, and its group holds the words of that length in input order.
//
// Example:
//   group_by_length({"to", "be", "or", "not"}) is {2: {"to", "be", "or"}, 3: {"not"}}
//   group_by_length({"elephant", "a", "cat", "I", "dog"})
//     is {1: {"a", "I"}, 3: {"cat", "dog"}, 8: {"elephant"}}
//   group_by_length({}) is {}
//
// The map keeps its keys sorted, so the shortest length comes first.
std::map<std::size_t, std::vector<std::string>> group_by_length(
    const std::vector<std::string>& words) {
    throw "TODO";
}
