// Exercise: std::vector basics
// Implement the five functions below.
//
// std::vector<int> v{3, 1, 4};  v.push_back(1);  v.size();  v[0];  v.back();
// for (int x : v) { ... }  visits each element.
//
// Note: v.size() returns std::size_t, an unsigned type. Comparing it with a
// negative int, or computing v.size() - 1 on an empty vector, goes wrong silently.
//
// ./grade 02_strings_vectors/02_vectors

#include <cstddef>
#include <vector>

int sum(const std::vector<int>& values) {
    throw "TODO";
}

// The average, or 0.0 for an empty vector.
double mean(const std::vector<int>& values) {
    throw "TODO";
}

// The even values, in their original order.
std::vector<int> evens(const std::vector<int>& values) {
    throw "TODO";
}

// Index of the largest value (the first one, if it appears more than once).
// Return -1 for an empty vector.
int index_of_max(const std::vector<int>& values) {
    throw "TODO";
}

// Each element is the sum of everything up to and including that position:
// running_total({1, 2, 3, 4}) == {1, 3, 6, 10}
std::vector<int> running_total(const std::vector<int>& values) {
    throw "TODO";
}
