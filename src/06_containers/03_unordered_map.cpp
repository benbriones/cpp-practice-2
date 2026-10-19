// Exercise: Hash maps
// std::unordered_map<Key, Value> is a hash table: average O(1) lookups, no ordering.
// It's the go-to tool for "have I seen this before, and where?" questions.
//     auto it = index.find(key);
//     if (it != index.end()) { use it->first (key) and it->second (value) }
//
// Grade: grade 06_containers/03_unordered_map

#include <algorithm>
#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

// Indices {i, j} with i < j and values[i] + values[j] == target, or std::nullopt.
// If several pairs work, return the one with the smallest j, and for that j the smallest i.
// Must run in O(n): one pass, remembering where each value was first seen.
std::optional<std::pair<std::size_t, std::size_t>> two_sum(const std::vector<int>& values,
                                                           int target) {
    throw "TODO";
}

// Index of the first character that appears exactly once in text, or std::nullopt.
// first_unique_char("swiss") == 1 (the 'w').
std::optional<std::size_t> first_unique_char(std::string_view text) {
    throw "TODO";
}

// Group words that are anagrams of each other (same letters, any order).
// Groups appear in the order their first word appears; words keep their input order.
// group_anagrams({"eat", "tea", "tan", "ate", "nat"}) == {{"eat", "tea", "ate"}, {"tan", "nat"}}
// Hint: anagrams are equal once sorted: std::sort(key.begin(), key.end()) on a copy.
std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& words) {
    throw "TODO";
}
