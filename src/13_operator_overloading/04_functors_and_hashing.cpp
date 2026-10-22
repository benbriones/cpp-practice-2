// === Lesson: Function objects and hashing ====================================
//
// A function object (functor) is a class with an operator(). Its objects are
// called like functions, and unlike a plain function they can carry data:
//
//     struct LongerThan {
//         std::size_t limit = 0;
//         bool operator()(const std::string& s) const { return s.size() > limit; }
//     };
//
//     LongerThan long_word{5};
//     long_word("hello");   // false
//     auto it = std::find_if(words.begin(), words.end(), LongerThan{5});
//
// A lambda is a function object the compiler writes for you; a capture becomes a
// member. A hand-written one has a type name, which a template argument needs.
// So containers take the type, and algorithms take an object:
//
//     std::set<Person, ByAge> people;                // the set creates its own ByAge
//     std::sort(list.begin(), list.end(), ByAge{});  // an object of it
//
// A comparator must behave like <. In particular cmp(a, a) is false, and the
// container treats two elements as the same when neither comes before the
// other. If ByAge compares only ages, a set keeps just one of two 30-year-olds.
// Break ties with another key: compare names when the ages are equal.
// std::tie(a.age, a.name) < std::tie(b.age, b.name) does exactly that.
//
// Hashing: unordered_set and unordered_map need a hash function and ==. The
// standard library hashes built-in types and strings; for your own type, pass a
// hasher type as the next template argument:
//
//     struct UsernameHash {
//         std::size_t operator()(const Username& u) const {
//             return std::hash<std::string>{}(u.text);   // reuse a standard hash
//         }
//     };
//     std::unordered_set<Username, UsernameHash> online;
//
// Equal values must hash equal. Different values should rarely collide, or
// lookups slow down. With several fields, combine their hashes so that order
// matters: h1 ^ h2 gives (1, 2) and (2, 1) the same hash, and every (n, n) a
// hash of 0. Multiplying one by a prime first, h1 * 31 + h2, keeps them apart.
//
// Unordered containers iterate in no particular order. When an answer depends
// on input order ("the first one"), walk the input and use the map for lookups.
//
// Read more: https://www.learncpp.com/cpp-tutorial/overloading-the-parenthesis-operator
//            https://en.cppreference.com/w/cpp/utility/hash
//
// === Challenge: Function objects and hashing =================================
// Write a comparator, a predicate and a hasher as function objects, then use them
// with the standard containers and algorithms.
//
// ./grade 13_operator_overloading/04_functors_and_hashing

#include <algorithm>
#include <cstddef>
#include <functional>
#include <optional>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Order strings by length, shortest first: less(a, b) is true when a comes before b.
// Strings of equal length fall back to alphabetical order,
// so two different strings never count as equal.
// A string never comes before itself.
//
// Example:
//   ByLength less;
//   less("a", "bb") and less("zz", "aaa") are true       // shorter wins
//   less("aa", "ab") is true, less("ab", "aa") is false  // same length: alphabetical
//   less("same", "same") is false
struct ByLength {
    bool operator()(const std::string& a, const std::string& b) const {
        throw "TODO";
    }
};

// Sort words in place using ByLength.
//
// Example:
//   words = {"ccc", "a", "bb", "aa", "b"}
//   sort_by_length(words);
//   // words is now {"a", "b", "aa", "bb", "ccc"}
void sort_by_length(std::vector<std::string>& words) {
    throw "TODO";
}

// Return the distinct words in ByLength order.
// Collect them in a std::set<std::string, ByLength>, which drops duplicates.
// An empty list gives an empty result.
//
// Example:
//   distinct_by_length({"pear", "fig", "apple", "fig", "kiwi", "pear"})
//   returns {"fig", "kiwi", "pear", "apple"}
//
// The set sorts with ByLength, so its elements are already in the right order.
std::vector<std::string> distinct_by_length(const std::vector<std::string>& words) {
    throw "TODO";
}

// A predicate with data: true when low <= value <= high.
// Both bounds are inclusive.
//
// Example:
//   InRange teens{13, 19};
//   teens(13), teens(15) and teens(19) are true; teens(12) and teens(20) are false
struct InRange {
    int low = 0;
    int high = 0;

    bool operator()(int value) const {
        throw "TODO";
    }
};

// Return how many values lie in [low, high], both bounds included.
// Use std::count_if with an InRange.
//
// Example:
//   count_in_range({1, 5, 10, 15, 20}, 5, 15) returns 3   // 5, 10 and 15
//   count_in_range({-3, -2, 0, 2}, -2, 1) returns 2       // -2 and 0
//   count_in_range({}, 0, 100) returns 0
int count_in_range(const std::vector<int>& values, int low, int high) {
    throw "TODO";
}

struct Point {
    int x = 0;
    int y = 0;

    bool operator==(const Point&) const = default;
};

std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

// Return a hash for p. Equal points must hash equal.
// Different points should rarely collide: the tests expect a 20 × 20 grid
// of points to produce at least 390 different hashes.
// x ^ y is a classic bad choice; try x * 31 + y on the std::hash values.
//
// Example:
//   PointHash hash;
//   hash(Point{3, 4}) == hash(Point{3, 4})
//   hash(Point{1, 2}) != hash(Point{2, 1})   // order matters
struct PointHash {
    std::size_t operator()(const Point& p) const {
        throw "TODO";
    }
};

// Return how many different points the list contains.
// Use std::unordered_set<Point, PointHash>.
//
// Example:
//   count_distinct({{0, 0}, {1, 2}, {0, 0}, {2, 1}, {1, 2}}) returns 3
//   count_distinct({}) returns 0
std::size_t count_distinct(const std::vector<Point>& points) {
    throw "TODO";
}

// Return the point that appears most often in points.
// Count with std::unordered_map<Point, int, PointHash>.
// On a tie, return the one that appears first in the list.
// Return std::nullopt for an empty list.
//
// Example:
//   most_visited({{0, 0}, {1, 1}, {1, 1}, {2, 2}, {1, 1}, {0, 0}}) is Point{1, 1}
//   most_visited({{2, 2}, {1, 1}, {1, 1}, {2, 2}}) is Point{2, 2}   // tie: first wins
//   most_visited({}) is std::nullopt
//
// The map iterates in no particular order, so settle ties by walking the list.
std::optional<Point> most_visited(const std::vector<Point>& points) {
    throw "TODO";
}
