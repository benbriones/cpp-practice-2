// Challenge: Build your own vector
// IntArray is a growable array of ints that manages its own heap block, the way
// std::vector does underneath. Implement every member function.
//
// Give it three private members: data_ (int*) pointing at a heap block of
// capacity_ ints, of which the first size_ are in use (both std::size_t). A
// new IntArray is empty: no block, size and capacity 0. When push_back finds
// the block full, allocate a new block twice the size (1 if the capacity is
// 0), copy the elements across, and delete[] the old block. The tests count
// allocations, so leaks and extra reallocations show up.
//
// ./grade 10_memory/05_dynamic_array

#include <cstddef>
#include <stdexcept>

class IntArray {
public:
    IntArray() = default;  // empty: no block allocated yet

    ~IntArray() {
        // TODO: free the block
    }

    // Copying is switched off: two IntArrays sharing one block would both
    // delete it. Module 11 shows how to make copies safely.
    IntArray(const IntArray&) = delete;
    IntArray& operator=(const IntArray&) = delete;

    std::size_t size() const {
        throw "TODO";
    }

    std::size_t capacity() const {
        throw "TODO";
    }

    // Append value, growing the block as described above when it's full.
    void push_back(int value) {
        throw "TODO";
    }

    // Remove the last element; capacity stays the same.
    // Throws std::out_of_range when the array is empty.
    void pop_back() {
        throw "TODO";
    }

    // The element at index. Throws std::out_of_range if index >= size().
    int at(std::size_t index) const {
        throw "TODO";
    }

    // Overwrite the element at index, with the same check as at().
    void set(std::size_t index, int value) {
        throw "TODO";
    }

    // Make the capacity at least n, keeping the elements and size(). If the
    // capacity is already n or more, do nothing (never shrink).
    void reserve(std::size_t n) {
        throw "TODO";
    }

private:
    // TODO: data members (give them default values so a new IntArray is empty)
};
