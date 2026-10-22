// === Lesson: Reading and writing through =====================================
//
// *p means "the box p points at". It isn't a copy of what's inside: it's the
// box itself, so it can sit on either side of =:
//
//     int x = 10;
//     int* p = &x;
//     int n = *p;               // reads x: n is 10, in a box of its own
//     *p = 99;                  // writes x: x is now 99, without naming x
//
// Two assignments, one character apart, doing very different things:
//
//     int x = 10;
//     int y = 20;
//     int* p = &x;              p --> x:10      y:20
//     p = &y;                   p --> y:20      x:10    p moved; no int changed
//     *p = 5;                   p --> y:5       x:10    the box p points at changed
//
// A reference can't be re-pointed. Once r names x, every use of r is x, so
// assigning to r copies a value into x:
//
//     int& r = x;
//     r = y;                    // means x = y. r still names x, not y
//
// So use a pointer when you need to switch targets, and a reference when the
// target is fixed for life.
//
// * and & each have two jobs. Next to a type they declare; in an expression
// they act:
//
//     int* p = &x;              // declares a pointer; takes x's address
//     int& r = *p;              // declares a reference; follows p to x
//
// Precedence. Postfix ++ and [] bind tighter than *:
//
//     ++*p      (*p)++          // both add 1 to the int p points at
//     *p++                      // moves p to the next box: almost never meant
//     *ptrs[i]                  // *(ptrs[i]): follow the i-th pointer in a vector
//
// const on a vector of pointers protects the vector, not the ints. With
// const std::vector<int*>& ptrs you can't add, remove or re-point ptrs[i], but
// *ptrs[i] = 0 compiles, because the elements are int*, not const int*.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/
//            https://www.learncpp.com/cpp-tutorial/pointers-and-const/
//
// === Exercise: Reading and writing through ===================================
// Predict the two traces on paper before you return an answer, then implement
// the three functions.
//
// ./grade 03b_more_references_pointers/02_dereferencing

#include <algorithm>
#include <utility>
#include <vector>

// Trace 3. What are x and y at the end? Return {x, y}.
//
//     int x = 1;
//     int y = 2;
//     int& r = x;
//     r = y;
//     r = 30;
//     y = 40;
std::pair<int, int> trace_3() { return {30, 40}; }

// Trace 4. What are n and m at the end? Return {n, m}.
//
//     int n = 5;
//     int* p = &n;
//     ++*p;
//     (*p)++;
//     *p = *p * 10;
//     int m = *p;
//     m += 1;
std::pair<int, int> trace_4() { return {70, 71}; }

// Rotate the three values that a, b and c point at one place to the left.
// a gets b's value, b gets c's, and c gets a's original value.
// None of the pointers is null.
//
// Example:
//   int x = 1;
//   int y = 2;
//   int z = 3;
//   rotate_three(&x, &y, &z);
//   // x is now 2, y is 3, z is 1
//
// Writes through the pointers, so the caller's variables change.
void rotate_three(int* a, int* b, int* c) {
    int temp_a = *a;

    *a = *b;
    *b = *c;
    *c = temp_a;
}

// Add amount to every int that the pointers in targets point at.
// Skip any pointer that is nullptr.
// A pointer that appears twice gets amount added twice.
//
// Example:
//   int x = 0;
//   int y = 0;
//   add_to_each({&x, &y, &x}, 3);   // x is now 6, y is 3
//   add_to_each({nullptr, &y}, 1);  // y is now 4
//
// targets is const, but the ints it points at can still be changed.
void add_to_each(const std::vector<int*>& targets, int amount) {
    for (int* t : targets) {
        if (!t) continue;

        *t += amount;
    }
}

// Return a pointer to whichever of *a and *b holds the larger value.
// If both values are equal, return a.
// Neither pointer is null.
//
// Example:
//   int x = 3;
//   int y = 8;
//   *larger_of(&x, &y) = 0;
//   // x is still 3, y is now 0
//
// The result points at the caller's variable, so writing through it changes that variable.
int* larger_of(int* a, int* b) {
    int* answer;

    if (*a == *b) return a;
    
    if (*a > *b) {
        answer = a;
    } else {
        answer = b;
    }

    return answer;
}
