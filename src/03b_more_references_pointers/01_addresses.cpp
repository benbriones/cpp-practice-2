// === Lesson: Addresses and aliases ===========================================
//
// Every variable is a box in memory, and every box has an address. In an
// expression, & asks for that address:
//
//     int x = 10;                  address 0x7ffd1234
//                                 +------------+
//                             x   |     10     |
//                                 +------------+
//
// A pointer is a box of its own, with its own address, whose value is the
// address of another box:
//
//     int* p = &x;
//
//           p                          x
//     +------------+            +------------+
//     | 0x7ffd1234 | ---------> |     10     |
//     +------------+            +------------+
//      at 0x7ffd9990             at 0x7ffd1234
//
// Learn this table. Every exercise in this module leans on it:
//
//     x     10              the value in x's box
//     &x    0x7ffd1234      where x's box is
//     p     0x7ffd1234      the address stored in p, so p == &x
//     *p    10              the value in the box p points at
//     &p    0x7ffd9990      where p's own box is
//
// A reference is not a box. It's a second name written on the same box, so it
// has the same address as the variable it refers to:
//
//     int& r = x;               x, r
//                          +------------+
//                          |     10     |      &r == &x, and writing r writes x
//                          +------------+
//
// Equal values and the same object are different questions. Compare values to
// ask "do these hold the same number?", and addresses to ask "is this the very
// same variable?":
//
//     int a = 10;
//     int b = 10;
//     a == b                    // true: same value
//     &a == &b                  // false: two different boxes
//
// Vector elements are boxes too. &v[2] is the address of the element itself,
// and a pointer p points at it exactly when p == &v[2]. Elements sit side by
// side, so each address is sizeof(int) bytes (usually 4) past the one before.
//
// Try it: add an int main() to this file that prints x, &x, p, *p and &p, then
// run grade --run 03b/01. Addresses print in hexadecimal and change from run to
// run, so never write code that depends on a particular one.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/
//            https://www.learncpp.com/cpp-tutorial/lvalue-references/
//
// === Exercise: Addresses and aliases =========================================
// The trace functions ask for a prediction, not code. Work the snippet out on
// paper first, then return your answer; the tests run the real snippet and tell
// you whether you were right. Then implement the three functions after them.
//
// ./grade 03b_more_references_pointers/01_addresses

#include <cstddef>
#include <utility>
#include <vector>

// Trace 1. What are a and b at the end? Return {a, b}.
//
//     int a = 1;
//     int b = 2;
//     int* p = &a;
//     int& r = b;
//     *p = 10;
//     r = 20;
//     p = &b;
//     *p += 5;
std::pair<int, int> trace_1() {
    throw "TODO";
}

// Trace 2. Which of these are true? Return their numbers in order, like {2, 4}.
//
//     int x = 7;
//     int y = 7;
//     int& r = x;
//     int* p = &y;
//
//     (1) x == y    (2) &x == &y    (3) &r == &x    (4) p == &r    (5) *p == r
std::vector<int> trace_2() {
    throw "TODO";
}

// True when a and b are the same variable, not merely two variables with equal values.
bool same_object(const int& a, const int& b) {
    throw "TODO";
}

// The index of the element p points at, or values.size() when p doesn't point
// into values (including when p is nullptr).
std::size_t index_of(const std::vector<int>& values, const int* p) {
    throw "TODO";
}

// A pointer to each element of values, in order, so writing through result[i]
// changes values[i].
std::vector<int*> pointers_to_each(std::vector<int>& values) {
    throw "TODO";
}
