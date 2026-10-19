// Exercise: Class templates
// Three small generic types. Write the member functions inside the class;
// each one is only compiled for the types you actually use it with.
//
// template <typename T, std::size_t N> takes a compile-time number as well as a
// type. RingBuffer<int, 3> and RingBuffer<int, 4> are different types.
//
// The tests write Pair p{1, 2.5}; without <int, double>. That's class template
// argument deduction (CTAD): the compiler works out A and B from the
// constructor's arguments.
//
// Grade: grade 15_templates/02_class_templates

#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

// A last-in, first-out stack.
template <typename T>
class Stack {
public:
    void push(const T& value) { throw "TODO"; }

    // Remove and return the top value. Throw std::out_of_range if the stack is empty.
    T pop() { throw "TODO"; }

    // The top value, without removing it. Throw std::out_of_range if the stack is empty.
    const T& top() const { throw "TODO"; }

    std::size_t size() const { throw "TODO"; }
    bool empty() const { throw "TODO"; }

private:
    std::vector<T> items_;
};

// Holds the N most recent values. Once full, each push overwrites the oldest
// value. Store them in the std::array below; no vector, no heap.
template <typename T, std::size_t N>
class RingBuffer {
public:
    void push(const T& value) { throw "TODO"; }

    // How many values are held right now (never more than N).
    std::size_t size() const { throw "TODO"; }

    // Always N.
    std::size_t capacity() const { throw "TODO"; }

    // The i-th oldest value held: at(0) is the oldest. Throw std::out_of_range if i >= size().
    const T& at(std::size_t i) const { throw "TODO"; }

    // Every value held, oldest first.
    std::vector<T> to_vector() const { throw "TODO"; }

private:
    std::array<T, N> slots_{};
    // TODO: add what you need to track where the oldest value is and how many there are.
};

// Two values of possibly different types.
template <typename A, typename B>
struct Pair {
    A first{};
    B second{};

    Pair(A a, B b) { throw "TODO"; }

    // The same values with their order reversed: Pair{1, 'x'}.swapped() is Pair<char, int>{'x', 1}.
    Pair<B, A> swapped() const { throw "TODO"; }
};
