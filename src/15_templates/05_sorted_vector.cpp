// Challenge: SortedVector
// A container that keeps its elements sorted at all times, so lookups can use
// binary search. Compare sets the order: std::less<T> (the default) is
// ascending, std::greater<T> is descending, or pass your own function object.
// Duplicates are allowed.
//
// std::lower_bound(first, last, value, compare) returns an iterator to the first
// element that isn't ordered before value; std::upper_bound to the first one
// ordered after it. Both take O(log n). Elements a and b are "equal" when
// neither compare(a, b) nor compare(b, a) is true.
//
// The tests insert 50,000 values and do 100,000 lookups, so a linear scan in
// insert or contains will time out.
//
// Grade: grade 15_templates/05_sorted_vector

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
    SortedVector(std::initializer_list<T> values) { throw "TODO"; }

    // Insert in order. A value equal to existing ones goes after them.
    void insert(const T& value) { throw "TODO"; }

    bool contains(const T& value) const { throw "TODO"; }

    // How many elements are equal to value.
    std::size_t count(const T& value) const { throw "TODO"; }

    // Remove one element equal to value. Return false if there wasn't one.
    bool erase(const T& value) { throw "TODO"; }

    std::size_t size() const { throw "TODO"; }

    // Read-only access by position: sorted[0] is the first element in order.
    const T& operator[](std::size_t index) const { throw "TODO"; }

    // Read-only iterators, so range-for and <algorithm> work but nobody can
    // break the order by writing through them.
    const_iterator begin() const { throw "TODO"; }
    const_iterator end() const { throw "TODO"; }

private:
    std::vector<T> items_;
    Compare compare_;
};
