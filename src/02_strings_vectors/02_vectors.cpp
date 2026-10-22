// === Lesson: std::vector =====================================================
//
// std::vector<T> (from <vector>) is a growable array of T, like a JavaScript
// array or Python list that holds one type. Like std::string it's a value:
// assigning it or passing it by value copies every element.
//
//     std::vector<int> v{3, 1, 4};     // the elements 3, 1, 4
//     std::vector<int> zeros(5);       // five 0s
//     std::vector<int> sevens(3, 7);   // 7, 7, 7: (count, value) needs parentheses
//     v.push_back(1);                  // 3, 1, 4, 1
//     v.size();  v.empty();  v.front();  v.back();  v.pop_back();
//
// v[i] doesn't check bounds: reading outside the vector is undefined behavior,
// which the grader's sanitizer reports. v.at(i) checks, and throws instead.
//
// A range-for visits each element. By value you get copies; to change the
// elements in place, iterate by reference with & (references come next module):
//
//     for (int x : v) { total += x; }
//     for (int &x : v) { x = -x; }       // negates every element of v
//
// The usual way to produce a vector is to build a local one and return it.
// Returning it doesn't copy the elements:
//
//     std::vector<int> squares_up_to(int n) {
//         std::vector<int> result;
//         for (int i = 1; i <= n; ++i) {
//             result.push_back(i * i);
//         }
//         return result;
//     }
//
// size() returns std::size_t, which is unsigned. Mixing it with signed ints
// goes wrong without an error:
//
//     int target = -1;
//     if (target < v.size()) { ... }    // false: -1 converts to a huge unsigned value
//     v.size() - 1                      // on an empty vector: 18446744073709551615
//
// The compiler warns about the first ("comparison of integers of different
// signs"); take that warning seriously. Use std::size_t for indexes, check
// empty() before computing size() - 1, or get a signed size with std::ssize(v)
// (C++20) or static_cast<int>(v.size()).
//
// Dividing by the size of an empty vector divides by zero, so handle the empty
// case first.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/
//            https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/
//
// === Exercise: std::vector basics ============================================
// Implement the five functions below.
//
// ./grade 02_strings_vectors/02_vectors

#include <cstddef>
#include <vector>

int sum(const std::vector<int> &values) {
    int sum = 0;

    for (std::size_t i = 0; i < values.size(); i++) {
        sum += values[i];
    }

    return sum;
}

// The average, or 0.0 for an empty vector.
double mean(const std::vector<int> &values) {
    if (values.empty()) return 0.0;
    int total = sum(values);
    return static_cast<double>(total) / values.size();
}

// The even values, in their original order.
std::vector<int> evens(const std::vector<int> &values) {
    std::vector<int> evenVals{};
    for (std::size_t i = 0; i < values.size(); i++) {
        if (values[i] % 2 == 0) {
            evenVals.push_back(values[i]);
        }
    }

    return evenVals;
}

// Index of the largest value (the first one, if it appears more than once).
// Return -1 for an empty vector.
int index_of_max(const std::vector<int> &values) {
    if (values.empty()) return -1;
    int currMax = values[0];
    int maxIndex = 0;

    for (std::size_t i = 0; i < values.size(); i++) {
        if (values[i] == currMax) {  // handle duplicate
            continue;
        } else if (values[i] > currMax) {
            currMax = values[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

// Each element is the sum of everything up to and including that position:
// running_total({1, 2, 3, 4}) == {1, 3, 6, 10}
std::vector<int> running_total(const std::vector<int> &values) {
    int currTotal = 0;
    std::vector<int> running_totals{};

    for (std::size_t i = 0; i < values.size(); i++) {
        currTotal += values[i];
        running_totals.push_back(currTotal);
    }

    return running_totals;
}
