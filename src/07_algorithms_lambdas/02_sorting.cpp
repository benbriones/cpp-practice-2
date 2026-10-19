// === Lesson: Sorting with comparators ========================================
//
// std::sort (from <algorithm>) sorts an iterator range in place, ascending:
//
//     std::vector<std::string> names{"Lin", "Ada", "Grace"};
//     std::sort(names.begin(), names.end());                    // Ada Grace Lin
//     std::sort(names.begin(), names.end(), std::greater<>());  // Lin Grace Ada
//
// The optional third argument is a comparator: a function or lambda (a, b) that
// returns true when a must come before b. It's a "less than" test, not Python's
// key= function or JavaScript's negative/zero/positive compare:
//
//     struct City { std::string country; int population; };
//     std::sort(cities.begin(), cities.end(), [](const City& a, const City& b) {
//         if (a.country != b.country) return a.country < b.country;  // A to Z
//         return a.population > b.population;          // then biggest first
//     });
//
// A comparator must return false when a and b are equal, so build it from < or >,
// never <= or >=. Breaking that rule is undefined behavior: std::sort can read
// past the end of the vector and crash.
//
// Stability: std::sort may reorder elements that compare equal. std::stable_sort
// takes the same arguments and keeps equal elements in their original order,
// which matters when the existing order should break ties.
//
// C++20's std::ranges::sort takes the whole container, plus an optional
// "projection" that picks the key to compare, a lot like Python's key=:
//
//     std::ranges::sort(cities, {}, &City::population);    // {} means the default <
//
// Two more tools from <algorithm>:
//
//     std::partial_sort(first, middle, last, comp)
//         puts the (middle - first) smallest elements, in order, at the front; the
//         rest are left in no particular order. middle must not be past last.
//     std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), comp)
//         compares two sequences the way a dictionary orders words, using comp
//         to compare one element of a with one element of b.
//
// std::greater<> lives in <functional>. <cctype>'s std::tolower and std::toupper
// take an int: pass static_cast<unsigned char>(c), because a negative char value
// is undefined behavior there.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-standard-library-algorithms/
//            https://en.cppreference.com/w/cpp/algorithm/stable_sort
//
// === Exercise: Sorting =======================================================
// Implement the functions below with the standard sorting algorithms.
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
