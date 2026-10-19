// Exercise: Function templates
// Write each function once so it works for any suitable type. The compiler
// generates a separate version for each type you call it with:
//
//     template <typename T>
//     T twice(const T& x) { return x + x; }   // twice(2) == 4, twice(std::string("ab")) == "abab"
//
// Every T in a call must deduce to the same type: count_matching(words, "the")
// won't compile when words is a vector<std::string>, because "the" is a
// const char*. Pass std::string("the") instead.
//
// Grade: grade 15_templates/01_function_templates

#include <cstddef>
#include <map>
#include <stdexcept>
#include <vector>

// The largest element; for strings that's the alphabetically last one.
// Throw std::invalid_argument if values is empty.
template <typename T>
T largest(const std::vector<T>& values) {
    throw "TODO";
}

// How many elements equal target.
template <typename T>
std::size_t count_matching(const std::vector<T>& values, const T& target) {
    throw "TODO";
}

// Exchange the values of a and b without calling std::swap.
template <typename T>
void swap_values(T& a, T& b) {
    throw "TODO";
}

// Keys become values and values become keys: {{"a", 1}, {"b", 2}} → {{1, "a"}, {2, "b"}}.
// If several keys share a value, keep the one that comes last in the original map.
template <typename K, typename V>
std::map<V, K> invert(const std::map<K, V>& original) {
    throw "TODO";
}

// Sum of the elements of any container you can loop over with range-for:
// std::vector, std::array, std::set... For strings, the sum is the concatenation.
// Start from  typename Container::value_type total{};  which is 0 for numbers and "" for strings.
template <typename Container>
typename Container::value_type sum(const Container& values) {
    throw "TODO";
}
