// === Lesson: Class templates =================================================
//
// A class template is a blueprint for a family of classes. Grid<int, 3, 2> and
// Grid<char, 8, 8> below are two unrelated types, each generated from the
// same code:
//
//     template <typename T, std::size_t Width, std::size_t Height>
//     class Grid {
//     public:
//         T& at(std::size_t x, std::size_t y) { return cells_[y * Width + x]; }
//         std::size_t cell_count() const { return Width * Height; }
//
//     private:
//         std::array<T, Width * Height> cells_{};
//     };
//
//     Grid<char, 8, 8> board;   // 64 chars, no heap allocation
//     board.at(0, 0) = 'R';
//
// Template parameters can be types (typename T) or compile-time values
// (std::size_t N, int, bool, ...). A value parameter is a constant, so it can
// size a std::array. The argument must be known at compile time: Grid<int, n, n>
// only works if n is constexpr.
//
// Inside the class, its plain name means the current instantiation: within
// Grid, `Grid` is short for Grid<T, Width, Height>. To name a different one,
// spell out its arguments, e.g. a member returning Grid<T, Height, Width>.
//
// Member functions are compiled only for the instantiations that call them. A
// method that uses T's < is fine to have, as long as nobody calls it with a T
// that has no <.
//
// Class template argument deduction (CTAD, C++17): when the constructor's
// parameters mention the template parameters, the compiler deduces them from
// the arguments, just as it does for function templates:
//
//     template <typename T>
//     struct Labeled {
//         std::string label;
//         T value;
//         Labeled(std::string l, T v) : label(std::move(l)), value(v) {}
//     };
//
//     Labeled temp{"celsius", 21.5};   // Labeled<double>
//     std::vector v{1, 2, 3};          // std::vector<int>, by the same mechanism
//
// Read more: https://www.learncpp.com/cpp-tutorial/class-templates/
//            https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/
//
// === Exercise: Class templates ===============================================
// Three small generic types. Write the member functions inside the class.
//
// The tests write Pair p{1, 2.5}; without <int, double>, so Pair relies on CTAD
// to work out A and B from the constructor's arguments.
//
// ./grade 15_templates/02_class_templates

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
