// === Lesson: Comparators and binary search ===================================
//
// Ordered containers and algorithms take "how to order" as a function object:
// something you call with two elements that returns true when the first goes
// before the second. std::set, std::map and std::sort all accept one.
//
//     std::less<int>{}(1, 2)      // true: it calls 1 < 2
//     std::greater<int>{}(1, 2)   // false: it calls 1 > 2
//
//     struct ByLength {           // your own: a struct with a const operator()
//         bool operator()(const std::string& a, const std::string& b) const {
//             return a.size() < b.size();
//         }
//     };
//     std::set<std::string, ByLength> words{"cat", "dog", "horse"};   // 2 words!
//
// A class template takes the comparator as a type parameter, usually with a
// default, and keeps an instance of it to call:
//
//     template <typename T, typename Compare = std::less<T>>
//     class TopList {
//         Compare better_;   // ... if (better_(a, b)) { a goes first } ...
//     };
//
// A comparator must behave like <, never like <=: compare(x, x) is false. Two
// elements are equivalent when neither goes before the other, so to ByLength
// "cat" and "dog" are the same, which is why the set above keeps only one.
// That's the only "equal" you get: T might not even have an ==.
//
// Binary search: on a range sorted by the same comparator, <algorithm> finds
// positions in O(log n) instead of scanning every element:
//
//     std::vector<int> times{10, 20, 20, 35, 50};
//     auto at = std::lower_bound(times.begin(), times.end(), 20);    // first not < 20
//     auto past = std::upper_bound(times.begin(), times.end(), 20);  // first > 20
//     at - times.begin();   // 1: subtracting iterators gives an index
//
// Either can return end() (try lower_bound for 60), so check before using *it.
// With a comparator, pass it last: std::lower_bound(first, last, value, compare).
//
// vector::insert(pos, value) and vector::erase(pos) take an iterator and shift
// the elements after it. Inside a const member function every data member is
// const, so items_.begin() there returns a const_iterator.
//
// Read more: https://en.cppreference.com/w/cpp/algorithm/lower_bound
//            https://en.cppreference.com/w/cpp/named_req/Compare
//
// === Challenge: SortedVector =================================================
// A container that keeps its elements sorted at all times, so lookups can use
// binary search. Compare sets the order: std::less<T> (the default) is
// ascending, std::greater<T> is descending, or pass your own function object.
// Duplicates are allowed.
//
// The tests insert 50,000 values and do 100,000 lookups, so a linear scan in
// insert or contains will time out.
//
// ./grade 15_templates/05_sorted_vector

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class SortedVector {
public:
    using const_iterator = typename std::vector<T>::const_iterator;

    SortedVector() = default;

    // Start with these values, given in any order.
    // Store them sorted by Compare; duplicates are kept.
    //
    // Example:
    //   SortedVector<int> sorted{3, 1, 2};                    // holds {1, 2, 3}
    //   SortedVector<int, std::greater<int>> desc{1, 3, 2};   // holds {3, 2, 1}
    SortedVector(std::initializer_list<T> values) { throw "TODO"; }

    // Insert value at its place in the order, so the elements stay sorted.
    // A value equal to existing ones goes after them.
    //
    // Example:
    //   SortedVector<int> sorted;
    //   for (int x : {5, 1, 4, 1, 3}) sorted.insert(x);
    //   // sorted now holds {1, 1, 3, 4, 5}.
    //
    // "Equal" means neither goes before the other under Compare. With a comparator
    // on priority only, inserting {2, "write"} then {2, "test"} keeps "write" first.
    void insert(const T& value) { throw "TODO"; }

    bool contains(const T& value) const { throw "TODO"; }

    // Return how many elements are equal to value.
    // Equal means neither goes before the other under Compare.
    //
    // Example:
    //   SortedVector<int> sorted{2, 2, 1, 2, 3};
    //   sorted.count(2) is 3, sorted.count(1) is 1, sorted.count(7) is 0
    //
    // Equal elements sit side by side, so binary search can find the whole run.
    std::size_t count(const T& value) const { throw "TODO"; }

    // Remove one element equal to value and return true.
    // Return false, changing nothing, if there wasn't one.
    //
    // Example:
    //   SortedVector<int> sorted{1, 2, 2, 3};
    //   sorted.erase(2) returns true, and sorted holds {1, 2, 3}
    //   sorted.erase(9) returns false, and size() is still 3
    //
    // Only one copy goes, even when several elements are equal to value.
    bool erase(const T& value) { throw "TODO"; }

    std::size_t size() const { throw "TODO"; }

    // Return the element at position index, read-only.
    // sorted[0] is the first element in order.
    //
    // Example:
    //   SortedVector<std::string> sorted{"pear", "apple", "fig"};
    //   sorted[0] is "apple", sorted[1] is "fig", sorted[2] is "pear"
    //
    // It returns a const reference, so nobody can break the order by writing through it.
    const T& operator[](std::size_t index) const { throw "TODO"; }

    // Return read-only iterators: begin() to the first element, end() one past the last.
    // Range-for and <algorithm> work with them, but nobody can break the order
    // by writing through them.
    //
    // Example:
    //   SortedVector<int> sorted{4, 1, 3};
    //   int total = 0;
    //   for (int x : sorted) total += x;   // visits 1, 3, 4: total is 8
    //   *sorted.begin() = 0;               // doesn't compile: the element is const
    //
    // That's why they return a const_iterator: *begin() is a const T&.
    const_iterator begin() const { throw "TODO"; }
    const_iterator end() const { throw "TODO"; }

private:
    std::vector<T> items_;
    Compare compare_;
};
