// === Lesson: Standard algorithms =============================================
//
// <algorithm> and <numeric> hold the loops you'd otherwise write by hand, much
// like JavaScript's filter/map/reduce/some/every. Most take an iterator range
// [first, last) and often a callable:
//
//     std::vector<double> prices{4.5, 12.0, 7.25};
//     auto cheap = std::count_if(prices.begin(), prices.end(),
//                                [](double p) { return p < 10; });       // 2
//
// Searches return an iterator, and last means "not found":
//
//     auto it = std::find_if(prices.begin(), prices.end(),
//                            [](double p) { return p > 10; });
//     if (it != prices.end()) {
//         auto index = std::distance(prices.begin(), it);   // 1, a signed ptrdiff_t
//     }
//
// Yes/no questions: std::all_of, std::any_of, std::none_of. On an empty range
// all_of and none_of are true and any_of is false, the usual logic for "every
// one of zero items".
//
// std::accumulate folds a range into one value, starting from an initial value.
// The running total has the type of that initial value, not of the elements:
//
//     std::accumulate(prices.begin(), prices.end(), 0.0);   // 23.75
//     std::accumulate(prices.begin(), prices.end(), 0);     // 23: each step drops
//                                                           // the fraction
//
// An optional fourth argument replaces + with any two-argument operation, such as
// a lambda or std::multiplies<>() from <functional>.
//
// std::transform writes f(x) for each x to an output iterator. std::back_inserter
// (from <iterator>) makes an output iterator that calls push_back:
//
//     std::vector<std::string> names{"Ada", "Bjarne", "Grace"};
//     std::vector<std::size_t> lengths;
//     std::transform(names.begin(), names.end(), std::back_inserter(lengths),
//                    [](const std::string& s) { return s.size(); });
//
// std::min_element and std::max_element return an iterator, std::minmax_element a
// pair of them. Each takes an optional comparator. On an empty range they return
// last, which you must not dereference:
//
//     auto by_size = [](const std::string& a, const std::string& b) {
//         return a.size() < b.size();
//     };
//     auto [shortest, longest] =
//         std::minmax_element(names.begin(), names.end(), by_size);
//
// C++20 adds versions in std::ranges that take the container itself:
// std::ranges::count_if(prices, pred). A std::string is a container of chars too,
// and text.find(c) returns std::string::npos when c isn't there.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-standard-library-algorithms/
//
// === Exercise: Standard algorithms ===========================================
// Each function below is one standard algorithm call plus a little glue. The
// tests can't see how you did it, so the discipline is yours: no hand-written loops.
//
// ./grade 07_algorithms_lambdas/03_algorithms

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
