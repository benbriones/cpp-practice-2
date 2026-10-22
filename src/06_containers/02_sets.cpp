// === Lesson: Sets ============================================================
//
// A set holds unique values: inserting a value that's already there does
// nothing. The standard library has two:
//
//     std::set<T>            kept sorted (a balanced tree): O(log n) operations,
//                            and loops visit the values smallest first
//     std::unordered_set<T>  a hash table: O(1) on average, in no useful order
//
// Python's set and JavaScript's Set are hash sets, like std::unordered_set.
// Reach for std::set when you need the order, and std::unordered_set when all
// you ask is "is it there?".
//
//     #include <set>
//
//     std::set<std::string> tags{"linux", "cpp", "linux"};   // {"cpp", "linux"}
//     tags.insert("algorithms");                             // sorts to the front
//     tags.erase("linux");
//
//     if (tags.contains("cpp")) { ... }          // C++20; count("cpp") gives 0 or 1
//     auto [pos, added] = tags.insert("cpp");    // added == false: already there
//
//     for (const std::string& tag : tags) {      // algorithms, cpp
//         std::cout << tag << '\n';
//     }
//
// insert() returns a pair: an iterator to the element, and a bool saying
// whether it was new. That bool answers "have I seen this before?" in the same
// step that records it.
//
// Any container can be built from another container's begin() and end(), and
// building a set that way drops the duplicates:
//
//     std::vector<int> ids{4, 1, 4, 9};
//     std::unordered_set<int> distinct(ids.begin(), ids.end());   // 3 values
//
// Why picking the right container matters: checking whether a value is in a
// vector means scanning it, O(n). Doing that once for each of n values is
// O(n²), which for 100'000 values is billions of steps, far past the grader's
// 5-second limit. A hash set answers each check in O(1) on average, so the
// whole job takes about 100'000 steps.
//
// Read more: https://en.cppreference.com/w/cpp/container/set
//            https://en.cppreference.com/w/cpp/container/unordered_set
//
// === Exercise: Sets ==========================================================
// Implement the four functions below.
//
// ./grade 06_containers/02_sets

#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

// Return the distinct values, smallest first.
// Each value appears once in the result, however often it appears in values.
//
// Example:
//   unique_sorted({3, 1, 3, 2}) is {1, 2, 3}
//   unique_sorted({5, -2, 5, 5, -2, 0}) is {-2, 0, 5}
//   unique_sorted({}) is {}
std::vector<int> unique_sorted(const std::vector<int>& values) {
    throw "TODO";
}

// Return the values that appear in both a and b.
// A value that repeats in a or b still appears once in the result.
//
// Example:
//   common_elements({1, 2, 3, 4}, {3, 4, 5}) is {3, 4}
//   common_elements({7, 7, 1}, {7}) is {7}
//   common_elements({1, 2}, {3, 4}) is {}
//
// The result is a std::set, so the values come out smallest first.
std::set<int> common_elements(const std::vector<int>& a, const std::vector<int>& b) {
    throw "TODO";
}

// Return true if any word appears more than once. Use a std::unordered_set.
// Case matters: "Red" and "red" are different words.
// An empty vector has no duplicates.
//
// Example:
//   has_duplicates({"red", "green", "red"}) is true
//   has_duplicates({"red", "green", "blue"}) is false
//   has_duplicates({"Red", "red"}) is false
//
// It must stay fast for 100'000 words: one hash-set check per word, not a scan.
bool has_duplicates(const std::vector<std::string>& words) {
    throw "TODO";
}

// Scan text left to right and return the first character you've already seen before.
// Return std::nullopt if no character repeats. Spaces count as characters too.
//
// Example:
//   first_repeated_char("abcbad") is 'b'   // the second b comes before the second a
//   first_repeated_char("hello") is 'l'
//   first_repeated_char("a  b") is ' '
//   first_repeated_char("abc") is std::nullopt
std::optional<char> first_repeated_char(std::string_view text) {
    throw "TODO";
}
