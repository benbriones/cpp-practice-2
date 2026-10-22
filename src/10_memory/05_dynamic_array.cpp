// === Lesson: How std::vector grows ===========================================
//
// A std::vector keeps its elements in one heap block. It tracks two numbers:
// size, the elements in use, and capacity, how many fit in the block. While
// size < capacity, push_back just writes into the next free slot. When the
// block is full it reallocates: get a bigger block, copy the elements across,
// free the old block, and switch over. You can watch it happen:
//
//     std::vector<int> v;
//     for (int i = 0; i < 9; ++i) {
//         v.push_back(i);
//         std::cout << v.size() << '/' << v.capacity() << ' ';
//     }
//     // libc++ prints: 1/1 2/2 3/4 4/4 5/8 6/8 7/8 8/8 9/16
//
// Why double rather than add one slot each time? Growing by one copies every
// element on every push_back: n pushes cost about n²/2 copies. Doubling copies
// 1 + 2 + 4 + ... < 2n elements in total, so push_back is O(1) on average
// ("amortized"). reserve(n) lets a caller who knows the final size skip the
// reallocations entirely.
//
// The order of those reallocation steps matters: the old block has to stay
// alive until its elements have been copied out of it. That's also why a
// pointer or reference into a vector dangles after a push_back that
// reallocates: the old block it pointed into is gone.
//
// A class that owns a heap block. Two pieces of class syntax help here. A
// default member initializer gives a member its value in every constructor
// that doesn't set it. A destructor, ~Name(), runs automatically when an
// object dies (goes out of scope, or is deleted), so it's where the block
// gets freed:
//
//     class Scratch {
//     public:
//         explicit Scratch(std::size_t n) : data_(new char[n]()), size_(n) {}
//         ~Scratch() { delete[] data_; }    // runs when a Scratch dies
//     private:
//         char *data_ = nullptr;            // default member initializers
//         std::size_t size_ = 0;
//     };
//
//     void work() {
//         Scratch buffer(1024);             // allocates
//     }                                     // buffer dies here: ~Scratch frees it
//
// Module 11 builds on this pattern (RAII). Throwing from a member function works
// as in module 08: throw std::out_of_range("..."); from <stdexcept>.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdvector-resizing-and-capacity/
//            https://www.learncpp.com/cpp-tutorial/destructors/
//
// === Challenge: Build your own vector ========================================
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
    IntArray(const IntArray &) = delete;
    IntArray &operator=(const IntArray &) = delete;

    std::size_t size() const {
        throw "TODO";
    }

    std::size_t capacity() const {
        throw "TODO";
    }

    // Append value after the last element.
    // When the block is full, grow it as described above: allocate twice the
    // capacity (1 if it's 0), copy the elements across, and delete[] the old block.
    //
    // Example:
    //   IntArray numbers;
    //   numbers.push_back(1);   // size 1, capacity 1
    //   numbers.push_back(2);   // size 2, capacity 2
    //   numbers.push_back(3);   // size 3, capacity 4
    //
    // While size < capacity, push_back just writes into the next free slot.
    void push_back(int value) {
        throw "TODO";
    }

    // Remove the last element; capacity stays the same.
    // Throw std::out_of_range when the array is empty.
    //
    // Example:
    //   numbers holds {1, 2, 3}, capacity 4
    //   numbers.pop_back();   // numbers holds {1, 2}, capacity is still 4
    //
    // The block isn't freed or shrunk, so a later push_back reuses the slot.
    void pop_back() {
        throw "TODO";
    }

    // Return the element at index.
    // Throw std::out_of_range if index >= size().
    //
    // Example:
    //   numbers holds {10, 20, 30}
    //   numbers.at(1) == 20
    //   numbers.at(3) throws std::out_of_range
    int at(std::size_t index) const {
        throw "TODO";
    }

    // Overwrite the element at index with value.
    // Use the same check as at(): throw std::out_of_range if index >= size().
    //
    // Example:
    //   numbers holds {1, 2}
    //   numbers.set(1, 99);   // numbers holds {1, 99}
    //   numbers.set(2, 5);    // throws std::out_of_range
    void set(std::size_t index, int value) {
        throw "TODO";
    }

    // Make the capacity at least n, keeping the elements and size().
    // If the capacity is already n or more, do nothing (never shrink).
    //
    // Example:
    //   numbers holds {4, 5}, capacity 2
    //   numbers.reserve(10);   // capacity 10, numbers still holds {4, 5}
    //   numbers.reserve(3);    // does nothing: capacity stays 10
    //
    // Reserving up front lets the next push_backs skip reallocating.
    void reserve(std::size_t n) {
        throw "TODO";
    }

private:
    // TODO: data members (give them default values so a new IntArray is empty)
};
