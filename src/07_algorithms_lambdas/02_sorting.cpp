// Exercise: Sorting
// std::sort(v.begin(), v.end()) sorts ascending. For any other order, pass a
// comparator as a third argument: a function or lambda (a, b) that returns true
// when a must come before b.
//
// ./grade 07_algorithms_lambdas/02_sorting

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

struct Person {
    std::string name;
    int age = 0;
};

// Largest first. The parameter is already a copy, so sort it and return it.
std::vector<int> sort_descending(std::vector<int> values) {
    throw "TODO";
}

// Shortest first. Words of equal length must keep their original order: std::sort
// doesn't promise that, std::stable_sort does.
std::vector<std::string> sort_by_length(std::vector<std::string> words) {
    throw "TODO";
}

// Youngest first; people of the same age ordered by name, A to Z.
void sort_people(std::vector<Person>& people) {
    throw "TODO";
}

// Alphabetical, ignoring case: "apple" < "Banana" < "cherry".
// std::lexicographical_compare takes a character comparator as its last argument.
std::vector<std::string> sort_ignoring_case(std::vector<std::string> words) {
    throw "TODO";
}

// The n largest values, largest first (all of them if n > size).
// std::partial_sort only sorts the front of the range, which is all you need.
std::vector<int> top_n(std::vector<int> values, std::size_t n) {
    throw "TODO";
}
