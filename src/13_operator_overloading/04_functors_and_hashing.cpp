// Challenge: Function objects and hashing
// A function object (functor) is a class with an operator(). Unlike a lambda,
// its type has a name, so it can be a template argument:
// std::set<std::string, ByLength> keeps its elements in ByLength order.
//
// std::unordered_set<Point> doesn't compile until it knows how to hash a Point.
// Pass a hasher type as the second template argument:
// std::unordered_set<Point, PointHash>.
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
