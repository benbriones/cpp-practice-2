// Exercise: Sets
// std::set<T> keeps unique values in sorted order; std::unordered_set<T> keeps unique
// values in no particular order but looks them up faster.
//     seen.insert(x);        // returns a pair; .second is false if x was already there
//     seen.contains(x);      // C++20
// You can build a set straight from a vector: std::set<int> s(v.begin(), v.end());
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
