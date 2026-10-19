// === Lesson: Function templates ==============================================
//
// A template is a recipe the compiler turns into real functions. You write the
// body once with a placeholder type T, and each call with a new type generates
// ("instantiates") a separate copy with T filled in:
//
//     template <typename T>
//     std::vector<T> repeat(const T& value, int times) {
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
//     typename Container::value_type first(const Container& c) { return *c.begin(); }
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
