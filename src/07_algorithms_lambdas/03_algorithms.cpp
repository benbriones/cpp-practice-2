// Exercise: Standard algorithms
// Each function below is one standard algorithm call plus a little glue. The
// tests can't see how you did it, so the discipline is yours: no hand-written loops.
//
//   <algorithm>: std::count_if, std::find_if, std::all_of, std::any_of,
//                std::transform, std::minmax_element
//   <numeric>:   std::accumulate (its initial value sets the type of the running total)
//
// Algorithms take an iterator range: std::count_if(v.begin(), v.end(), predicate).
//
// Grade: grade 07_algorithms_lambdas/03_algorithms

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

// How many words are longer than `length` characters.
int count_longer_than(const std::vector<std::string>& words, std::size_t length) {
    throw "TODO";
}

// Index of the first negative value, or -1 if there is none.
// std::distance(v.begin(), it) turns an iterator into an index.
int first_negative_index(const std::vector<int>& values) {
    throw "TODO";
}

// True if every value is positive. An empty vector counts as true.
bool all_positive(const std::vector<int>& values) {
    throw "TODO";
}

// True if any word contains the given letter.
bool any_contains(const std::vector<std::string>& words, char letter) {
    throw "TODO";
}

// The product of all values; 1 for an empty vector. Must not overflow an int.
long long product(const std::vector<int>& values) {
    throw "TODO";
}

// Each value squared, in order. std::back_inserter(out) lets std::transform push_back.
std::vector<int> squares(const std::vector<int>& values) {
    throw "TODO";
}

// Largest minus smallest value; 0 for an empty vector.
int spread(const std::vector<int>& values) {
    throw "TODO";
}
