// === Lesson: Hash maps =======================================================
//
// std::unordered_map<Key, Value> is a hash table, the same idea as a Python
// dict or a JS Map: lookups, inserts and erases are O(1) on average. It keeps
// no order, not even the insertion order a Python dict or JS Map keeps, but
// otherwise the interface is almost the same as std::map's:
//
//     #include <unordered_map>
//
//     std::unordered_map<std::string, int> ages{{"ada", 36}, {"alan", 41}};
//     ages["grace"] = 85;                  // insert or overwrite
//     ages.insert({"ada", 99});            // no effect: "ada" is already there
//     ages.insert_or_assign("ada", 37);    // overwrites
//
//     auto it = ages.find("alan");         // look up once...
//     if (it != ages.end()) {              // ...end() means "not found"
//         std::cout << it->first << " is " << it->second << '\n';
//     }
//
//     ages.contains("bob");                // false, and nothing is inserted
//     ages["bob"];                         // inserts "bob" with 0, as std::map does
//
// Hash maps are the standard way to trade memory for time. A question shaped
// like "have I seen this before, and where or how often?" can be answered in
// one pass, by remembering what you've seen so far instead of searching back
// through the data each time:
//
//     std::unordered_map<std::string, int> visits;
//     for (const std::string &page : page_views) {
//         if (++visits[page] == 2) std::cout << "first repeat visit: " << page << '\n';
//     }
//
// Searching back costs O(n) per element, O(n²) in all: for 200'000 values,
// about 20 billion steps and a timeout. One hash lookup per element is O(n).
//
// No order: a loop over an unordered_map visits entries in an order that
// depends on the hashing, and it can change as the map grows. When a result
// has to come out in input order, loop over the input (or a vector you filled
// in order) and use the map only for lookups.
//
// Keys need a hash function. Built-in types and std::string have one; std::pair
// and your own structs don't (module 13 shows how to add one). std::map only
// needs < instead.
//
// Read more: https://en.cppreference.com/w/cpp/container/unordered_map
//
// === Exercise: Hash maps =====================================================
// Implement the three functions below.
//
// ./grade 06_containers/03_unordered_map

#include <algorithm>
#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

// Return indices {i, j} with i < j and values[i] + values[j] == target.
// Return std::nullopt if no such pair exists.
// If several pairs work, return the one with the smallest j, and for that j the smallest i.
// Must run in O(n): one pass, remembering where each value was first seen.
//
// Example:
//   two_sum({2, 7, 11, 15}, 9) is {0, 1}
//   two_sum({1, 4, 4, 3, 0}, 4) is {0, 3}   // j = 3 is the smallest j that works
//   two_sum({3, 3}, 6) is {0, 1}            // equal values at different indices are fine
//   two_sum({3, 5}, 6) is std::nullopt      // the same index can't be used twice
std::optional<std::pair<std::size_t, std::size_t>> two_sum(const std::vector<int> &values,
                                                           int target) {
    throw "TODO";
}

// Return the index of the first character that appears exactly once in text.
// Return std::nullopt if no character appears exactly once, or text is empty.
//
// Example:
//   first_unique_char("swiss") is 1      // the 'w'
//   first_unique_char("aabbc") is 4      // the 'c'
//   first_unique_char("aabb") is std::nullopt
std::optional<std::size_t> first_unique_char(std::string_view text) {
    throw "TODO";
}

// Group words that are anagrams of each other (same letters, any order).
// Groups appear in the order their first word appears; words keep their input order.
// A repeated word is kept, in its group, each time it appears.
//
// Example:
//   group_anagrams({"eat", "tea", "tan", "ate", "nat"})
//     is {{"eat", "tea", "ate"}, {"tan", "nat"}}
//   group_anagrams({"ab", "ba", "ab"}) is {{"ab", "ba", "ab"}}
//   group_anagrams({}) is {}
//
// Hint: anagrams are equal once sorted: std::sort(key.begin(), key.end()) on a copy.
std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string> &words) {
    throw "TODO";
}
