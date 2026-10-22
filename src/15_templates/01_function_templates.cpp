// === Lesson: Function templates ==============================================
//
// A template is a recipe the compiler turns into real functions. You write the
// body once with a placeholder type T, and each call with a new type generates
// ("instantiates") a separate copy with T filled in:
//
//     template <typename T>
//     std::vector<T> repeat(const T &value, int times) {
//         std::vector<T> result;
//         for (int i = 0; i < times; ++i) result.push_back(value);
//         return result;
//     }
//
//     repeat(7, 3);                   // T = int: {7, 7, 7}
//     repeat(std::string("ab"), 2);   // T = std::string: {"ab", "ab"}
//     repeat<double>(1, 2);           // T given explicitly: {1.0, 1.0}
//
// Unlike TypeScript generics, nothing is erased: each instantiation is compiled
// and type-checked for its own T. The body may use any operation on T (+, <,
// ==, <<) and only fails to compile when called with a type that lacks it. The
// error then points inside your template; exercise 03 shows how to do better.
//
// Deduction: the compiler works out T from the arguments, and every use of T
// must agree. With template <typename T> T bigger(T a, T b):
//
//     bigger(3, 4);             // T = int
//     bigger(3, 4.5);           // error: is T int or double?
//     bigger<double>(3, 4.5);   // fine: T is given, and 3 converts
//
// A string literal is a char array (const char[N]), not a std::string, so it
// deduces a different T. It turns into a const char* when copied, and < on two
// const char* compares addresses, not text.
//
// A template can have several parameters: template <typename K, typename V>
// can take a std::map<K, V> and deduce both from it.
//
// Nested types: a name like Container::value_type depends on what Container
// turns out to be, so C++ needs `typename` in front to know it names a type:
//
//     template <typename Container>
//     typename Container::value_type first(const Container &c) { return *c.begin(); }
//
// T{} is a value-initialized T: 0 for numbers, "" for std::string, an empty
// vector for std::vector. It's the generic way to write "a zero of this type".
//
// Read more: https://www.learncpp.com/cpp-tutorial/function-templates/
//            https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
//
// === Exercise: Function templates ============================================
// Write each function once so it works for any suitable type.
//
// Every T in a call must deduce to the same type: count_matching(words, "the")
// won't compile when words is a vector<std::string>, because "the" is a char
// array. Pass std::string("the") instead.
//
// ./grade 15_templates/01_function_templates

#include <cstddef>
#include <map>
#include <stdexcept>
#include <vector>

// Return the largest element in values.
// For strings, that's the one that comes last alphabetically.
// Throw std::invalid_argument if values is empty.
//
// Example:
//   largest(std::vector<int>{3, 9, 2}) is 9
//   largest(std::vector<int>{-5, -2, -9}) is -2
//   largest(std::vector<std::string>{"pear", "apple", "zucchini", "fig"}) is "zucchini"
//   largest(std::vector<int>{}) throws std::invalid_argument
//
// The same body works for any T that can be compared with <.
template <typename T>
T largest(const std::vector<T> &values) {
    throw "TODO";
}

// Return how many elements of values equal target.
// An empty vector, or one with no match, gives 0.
//
// Example:
//   count_matching(std::vector<int>{1, 2, 1, 3, 1}, 1) is 3
//   words = {"the", "cat", "the", "hat"}
//   count_matching(words, std::string("the")) is 2
//
// target has the same type T as the elements, so pass std::string("the"), not "the".
template <typename T>
std::size_t count_matching(const std::vector<T> &values, const T &target) {
    throw "TODO";
}

// Exchange the values of a and b without calling std::swap.
// It must work for ints, strings, even whole vectors.
//
// Example:
//   int a = 1;
//   int b = 2;
//   swap_values(a, b);
//   // a is now 2, b is now 1.
//
// a and b are references, so the swap changes the caller's variables.
template <typename T>
void swap_values(T &a, T &b) {
    throw "TODO";
}

// Return a new map where each key becomes a value and each value becomes a key.
// If several keys share a value, keep the one that comes last in the original map.
// An empty map gives an empty map.
//
// Example:
//   original = {{"a", 1}, {"b", 2}}
//   invert(original) is {{1, "a"}, {2, "b"}}
//   sizes = {{"ant", 1}, {"bee", 1}, {"cow", 3}}
//   invert(sizes) is {{1, "bee"}, {3, "cow"}}   // "bee" comes after "ant"
//
// A std::map is sorted by key, so "last" means the largest key with that value.
template <typename K, typename V>
std::map<V, K> invert(const std::map<K, V> &original) {
    throw "TODO";
}

// Return the sum of the elements of any container you can loop over with range-for:
// std::vector, std::array, std::set...
// For strings, the sum is the concatenation.
// Start from  typename Container::value_type total{};  which is 0 for numbers
// and "" for strings, so an empty container gives 0 (or "").
//
// Example:
//   sum(std::vector<int>{1, 2, 3, 4}) is 10
//   sum(std::set<int>{5, 5, 10}) is 15, because a set holds 5 only once
//   sum(std::vector<std::string>{"ab", "cd", "e"}) is "abcde"
//   sum(std::vector<int>{}) is 0
template <typename Container>
typename Container::value_type sum(const Container &values) {
    throw "TODO";
}
