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

// The distinct values, smallest first: unique_sorted({3, 1, 3, 2}) == {1, 2, 3}.
std::vector<int> unique_sorted(const std::vector<int>& values) {
    throw "TODO";
}

// Values that appear in both a and b.
std::set<int> common_elements(const std::vector<int>& a, const std::vector<int>& b) {
    throw "TODO";
}

// True if any word appears more than once. Use a std::unordered_set.
bool has_duplicates(const std::vector<std::string>& words) {
    throw "TODO";
}

// Scan left to right and return the first character you've already seen before:
// "abcbad" gives 'b' (the second b comes before the second a). std::nullopt if none.
std::optional<char> first_repeated_char(std::string_view text) {
    throw "TODO";
}
