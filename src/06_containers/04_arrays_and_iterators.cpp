// === Lesson: std::array and iterators ========================================
//
// std::array<T, N> is a fixed-size array whose size is part of its type. Unlike
// a C array (module 10), it knows its size, and it can be copied, compared with
// == and returned from functions:
//
//     #include <array>
//
//     std::array<double, 7> rainfall{};    // 7 zeros: {} value-initializes
//     rainfall[2] = 4.5;                   // unchecked, like a vector's []
//     rainfall.at(9);                      // checked: throws std::out_of_range
//     auto copy = rainfall;                // copies all 7 elements
//     bool same = (copy == rainfall);      // true
//
// Without the {}, a local std::array<int, N> starts out full of garbage.
//
// An iterator is a position in a container, much like a cursor. Every standard
// container has them:
//
//     c.begin()  the first element    c.end()  one past the last element
//     *it        the element at it    it->x    a member of that element
//     ++it       the next position    it - c.begin()  its index (vectors and strings)
//
//     std::vector<int> v{4, 8, -1, 7};
//     for (auto it = v.begin(); it != v.end(); ++it) {
//         if (*it < 0) {
//             std::cout << "first negative at index " << (it - v.begin()) << '\n';
//             break;
//         }
//     }
//
// A range-for loop is this same loop, written for you. You need the explicit
// form when the loop changes the container itself, as erase() and insert() do.
// A std::map iterator points at a key/value pair: it->first and it->second.
//
// Invalidation: changing a container can leave existing iterators pointing at
// nothing. erase(it) invalidates `it` (and in a vector, every iterator after
// it), and insert() into a vector may move all of its elements. Using an
// invalidated iterator is undefined behavior: the loop may skip elements, run
// past the end, or crash:
//
//     for (auto it = v.begin(); it != v.end(); ++it) {
//         if (*it < 0) v.erase(it);    // bug: `it` is invalid, then ++it uses it
//     }
//
// That's why both functions return a fresh iterator: erase() returns the
// position after the removed element, insert() the position of the new one.
// insert(it, x) puts x before `it`, so insert(v.end(), x) appends.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-stdarray/
//            https://www.learncpp.com/cpp-tutorial/introduction-to-iterators/
//
// === Exercise: Arrays and iterators ==========================================
// Implement the four functions below. To erase while looping, continue from the
// iterator that erase() returns:
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
