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
