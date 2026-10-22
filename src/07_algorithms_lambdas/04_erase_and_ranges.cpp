// === Lesson: Erasing elements, and views =====================================
//
// C++20 can remove matching elements from a vector (or string, deque, list) in
// one call. Both return how many elements they removed:
//
//     std::vector<int> scores{70, 45, 88, 45, 92};
//     std::erase(scores, 45);                                  // {70, 88, 92}
//     std::erase_if(scores, [](int s) { return s > 90; });     // {70, 88}
//
// Older code uses the "erase-remove idiom", and it's worth understanding because
// other algorithms work the same way. std::remove_if can't change a container's
// size, since it only sees iterators. It moves the elements to keep to the front
// and returns an iterator to the new logical end; erase then cuts off the tail:
//
//     auto new_end = std::remove_if(v.begin(), v.end(), pred);   // size unchanged
//     v.erase(new_end, v.end());                                  // now it shrinks
//
// Forget the erase and the vector keeps its old size, with leftover values at
// the end.
//
// std::unique follows the same pattern: it collapses each run of equal *adjacent*
// elements into one, returns the new logical end, and leaves the erase to you.
// After the erase, {1, 1, 2, 1} is {1, 2, 1}: the last 1 wasn't next to the others.
//
// Views (<ranges>) are lazy sequences built on top of a container. They don't
// copy the container; each element is computed only when a loop asks for it. Adaptors
// chain with |, like a shell pipeline:
//
//     std::vector<std::string> names{"Ada", "Bjarne", "Grace", "Linus", "Ken"};
//     auto initials = names
//         | std::views::filter([](const std::string& n) { return n.size() > 3; })
//         | std::views::transform([](const std::string& n) { return n[0]; })
//         | std::views::take(2);
//     for (char c : initials) std::cout << c;                 // BG
//
// std::views::take(n) stops after n elements, or sooner if the input runs out.
// A view refers to its container, so don't let it outlive the container, and
// don't add or remove elements while you're iterating a view over it.
//
// C++20 can't convert a view straight into a vector (C++23 adds
// std::ranges::to), so loop over the view and push_back each element.
//
// Read more: https://en.cppreference.com/w/cpp/container/vector/erase2
//            https://en.cppreference.com/w/cpp/ranges
//
// === Exercise: Erasing and ranges ============================================
// Removing elements from containers, and a first taste of C++20 ranges.
//
// ./grade 07_algorithms_lambdas/04_erase_and_ranges

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string>
#include <vector>

// Remove every negative value from values, in place.
// The values that stay keep their original order. 0 is not negative.
//
// Example:
//   values = {3, -1, 4, -1, -5, 9}
//   remove_negatives(values);
//   values is now {3, 4, 9}
//
// Modifies the original vector, so its size shrinks; does not return anything.
void remove_negatives(std::vector<int>& values) {
    throw "TODO";
}

// Remove every word with fewer than min_length characters, in place.
// Words exactly min_length long stay. The words that stay keep their order.
//
// Example:
//   words = {"a", "tree", "is", "green", "and", "tall"}
//   remove_short_words(words, 4);
//   words is now {"tree", "green", "tall"}
//
// Modifies the original vector; does not return anything.
void remove_short_words(std::vector<std::string>& words, std::size_t min_length) {
    throw "TODO";
}

// Return values sorted ascending, with duplicates removed.
// Each distinct value appears exactly once.
// std::unique only removes *adjacent* repeats and returns the new logical end.
//
// Example:
//   dedupe({3, 1, 3, 2, 1}) is {1, 2, 3}
//   dedupe({5, 5, 5}) is {5}
//   dedupe({-2, 7, -2, 0}) is {-2, 0, 7}
std::vector<int> dedupe(std::vector<int> values) {
    throw "TODO";
}

// Return text with each run of the same character collapsed to one character.
// Only repeats right next to each other collapse; the same letter later on stays.
// A std::string is a container too, so std::unique works on it.
//
// Example:
//   squeeze("aaabccdddd") is "abcd"
//   squeeze("mississippi") is "misisipi"
//   squeeze("abc") is "abc"
std::string squeeze(std::string text) {
    throw "TODO";
}

// Return the squares of the first n even values, in order.
// If there are fewer than n even values, return the squares of all of them.
// Write it as one view pipeline.
//
// Example:
//   first_n_even_squares({1, 2, 3, 4, 5, 6}, 2) is {4, 16}
//   first_n_even_squares({10, 7, -2, 0}, 3) is {100, 4, 0}
//   first_n_even_squares({1, 2, 3}, 5) is {4}
//
// The view only computes elements as the loop asks for them, then you push_back each.
std::vector<int> first_n_even_squares(const std::vector<int>& values, std::size_t n) {
    throw "TODO";
}
