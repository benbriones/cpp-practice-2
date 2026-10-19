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

// Orders strings by length, shortest first. Strings of equal length fall back
// to alphabetical order, so two different strings never count as equal.
struct ByLength {
    bool operator()(const std::string& a, const std::string& b) const {
        throw "TODO";
    }
};

// Sorts words in place using ByLength.
void sort_by_length(std::vector<std::string>& words) {
    throw "TODO";
}

// The distinct words in ByLength order. Collect them in a std::set<std::string, ByLength>.
std::vector<std::string> distinct_by_length(const std::vector<std::string>& words) {
    throw "TODO";
}

// A predicate with data: true when low <= value <= high.
struct InRange {
    int low = 0;
    int high = 0;

    bool operator()(int value) const {
        throw "TODO";
    }
};

// How many values lie in [low, high]: std::count_if with an InRange.
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

// Equal points must hash equal, and different points should rarely collide:
// the tests expect a 20 × 20 grid of points to produce at least 390 different
// hashes. (x ^ y is a classic bad choice; try x * 31 + y on the std::hash values.)
struct PointHash {
    std::size_t operator()(const Point& p) const {
        throw "TODO";
    }
};

// How many different points the list contains. Use std::unordered_set<Point, PointHash>.
std::size_t count_distinct(const std::vector<Point>& points) {
    throw "TODO";
}

// The point that appears most often, counted with std::unordered_map<Point, int, PointHash>.
// On a tie, the one that appears first in the list. std::nullopt for an empty list.
std::optional<Point> most_visited(const std::vector<Point>& points) {
    throw "TODO";
}
