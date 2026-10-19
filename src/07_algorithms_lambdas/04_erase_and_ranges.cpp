// Exercise: Erasing and ranges
// Removing elements from containers, and a first taste of C++20 ranges.
//
// std::erase_if(v, predicate) removes every matching element (C++20). In older
// code you'll see the "erase-remove idiom": v.erase(std::remove_if(...), v.end()).
//
// Views (<ranges>) are lazy: they produce elements only as you iterate, and they
// chain with |:   for (int x : v | std::views::filter(pred) | std::views::take(3))
// C++20 can't collect a view straight into a vector, so push_back in a loop.
//
// ./grade 07_algorithms_lambdas/04_erase_and_ranges

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string>
#include <vector>

// Remove every negative value; the rest keep their order.
void remove_negatives(std::vector<int>& values) {
    throw "TODO";
}

// Remove words with fewer than min_length characters.
void remove_short_words(std::vector<std::string>& words, std::size_t min_length) {
    throw "TODO";
}

// Sorted, with duplicates removed: dedupe({3, 1, 3, 2, 1}) == {1, 2, 3}.
// std::unique only removes *adjacent* repeats and returns the new logical end.
std::vector<int> dedupe(std::vector<int> values) {
    throw "TODO";
}

// Collapse runs of the same character: squeeze("aaabccdddd") == "abcd".
// A std::string is a container too, so std::unique works on it.
std::string squeeze(std::string text) {
    throw "TODO";
}

// Squares of the first n even values, in order:
// first_n_even_squares({1, 2, 3, 4, 5, 6}, 2) == {4, 16}. Write it as one view pipeline.
std::vector<int> first_n_even_squares(const std::vector<int>& values, std::size_t n) {
    throw "TODO";
}
