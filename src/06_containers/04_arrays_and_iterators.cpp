// Exercise: Arrays and iterators
// std::array<T, N> is a fixed-size array that knows its size and can be copied and
// compared. std::array<int, 26> counts{};  starts as 26 zeros.
//
// An iterator marks a position in a container: begin() is the first element, end() is one
// past the last, ++it moves forward, *it is the element. erase(it) removes an element and
// returns an iterator to the one after it; the old iterator is now invalid, so always
// continue from the returned one:
//     for (auto it = c.begin(); it != c.end(); ) { if (...) it = c.erase(it); else ++it; }
//
// ./grade 06_containers/04_arrays_and_iterators

#include <array>
#include <cctype>
#include <cstddef>
#include <map>
#include <string>
#include <string_view>
#include <vector>

// How often each letter a–z appears, ignoring case; other characters are skipped.
// Index 0 counts 'a', index 25 counts 'z'.
std::array<int, 26> letter_counts(std::string_view text) {
    throw "TODO";
}

// Erase every entry whose score is below threshold. Use an iterator loop with erase().
void remove_below(std::map<std::string, int>& scores, int threshold) {
    throw "TODO";
}

// Erase every word shorter than min_length, keeping the rest in order. Iterator loop again.
// (C++20 also has std::erase_if, which you'll meet with lambdas in module 07.)
void remove_short_words(std::vector<std::string>& words, std::size_t min_length) {
    throw "TODO";
}

// values is sorted ascending. Insert value at the right place so it stays sorted: walk an
// iterator to the first element greater than value, then values.insert(it, value).
void insert_sorted(std::vector<int>& values, int value) {
    throw "TODO";
}
