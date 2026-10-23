// === Lesson: Pointers to pointers, and pointers to containers ================
//
// A pointer parameter is passed by value: the function gets its own copy of the
// address. The copy still leads to the caller's box, so *p = ... reaches it, but
// p = ... only moves the copy (03b_more_references_pointers/04_parameters).
//
// To move the caller's pointer, the function needs the pointer's own box. A
// reference to it (int *&p) is one way. The C way is to pass its address, a
// pointer to a pointer:
//
//     int x = 1;
//     int *p = &x;
//     int **pp = &p;
//
//         pp               p                x
//     +--------+       +--------+       +--------+
//     |   &p   | ----> |   &x   | ----> |   1    |
//     +--------+       +--------+       +--------+
//
//     pp        the address of p
//     *pp       p itself: *pp = &y re-points p
//     **pp      x: **pp = 5 writes x
//
//     void retarget(int **pp, int *target) { *pp = target; }
//     retarget(&p, &y);         // p now points at y. Note the &p at the call
//
// int *&p and int **pp do the same job. The reference needs no extra * inside
// the function and can't be null. The pointer shows & at the call site, and the
// caller may pass nullptr when the function allows it.
//
// Pointers to containers. Take a std::vector or std::string by pointer when the
// caller may have none to give. Reach members with ->, and index through *:
//
//     int first_or_zero(const std::vector<int> *v) {
//         if (v == nullptr || v->empty()) return 0;
//         return (*v)[0];
//     }
//
//     for (int x : *v) { ... }  // range-for over the vector v points at
//
// Watch out for v[0] there: it compiles, because a pointer can be indexed like
// an array. v[0] happens to mean *v, the whole vector, and v[1] is whatever
// memory sits after it. Always write (*v)[i] or v->at(i).
//
// const in a pointer parameter, read right to left:
//
//     const int *p          pointer to a const int: can't write *p, can re-point p
//     int *const p          const pointer to an int: can write *p, can't re-point p
//
// Read more: https://www.learncpp.com/cpp-tutorial/pointers-to-pointers/
//            https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/
//
// === Exercise: Pointers to pointers, and pointers to containers ==============
// Predict the trace, then implement the four functions.
//
// ./grade 03c_even_more_references_pointers/04_pointer_parameters

#include <cstddef>
#include <vector>

// Trace 6. What are x, y and *p at the end? Return {x, y, *p}.
//
//     void set_target(int **pp, int *target) { *pp = target; }
//     void bump_target(int **pp) { **pp += 1; }
//     void lose_target(int *p) { p = nullptr; }
//
//     int x = 1;
//     int y = 10;
//     int *p = &x;
//     bump_target(&p);
//     set_target(&p, &y);
//     bump_target(&p);
//     lose_target(p);
//     *p *= 2;
std::vector<int> trace_6() {
    throw "TODO";
}

// Return the sum of the vector values points at, or fallback when values is nullptr.
// An empty vector sums to 0: it's a real vector, not a missing one.
//
// Example:
//   std::vector<int> v{1, 2, 3};
//   sum_or(&v, -1) is 6
//   sum_or(nullptr, -1) is -1
//   std::vector<int> empty;
//   sum_or(&empty, -1) is 0
//
// values is a pointer to a whole vector, so reach its elements through *values.
int sum_or(const std::vector<int> *values, int fallback) {
    throw "TODO";
}

// Append value to the vector values points at.
// If limit isn't nullptr and value is greater than *limit, append *limit instead.
// values is never null.
//
// Example:
//   std::vector<int> v;
//   int cap = 10;
//   push_clamped(&v, 4, &cap);      // v is now {4}
//   push_clamped(&v, 50, &cap);     // v is now {4, 10}
//   push_clamped(&v, 50, nullptr);  // v is now {4, 10, 50}
//
// limit is an optional input: nullptr means "no limit".
void push_clamped(std::vector<int> *values, int value, const int *limit) {
    throw "TODO";
}

// Swap where *a and *b point. The ints themselves don't change.
// Neither a nor b is null.
//
// Example:
//   int x = 1;
//   int y = 2;
//   int *p = &x;
//   int *q = &y;
//   swap_pointers(&p, &q);
//   // p now points at y and q at x. x is still 1, y is still 2
//
// a and b are pointers to the caller's pointers, so *a is the caller's p itself.
void swap_pointers(int **a, int **b) {
    throw "TODO";
}

// Point *out at the largest element of values and return true.
// If several elements tie for largest, point at the first one.
// If values is empty, return false and leave *out alone. out is never null.
//
// Example:
//   values = {3, 9, 4, 9}
//   int *best = nullptr;
//   point_at_max(values, &best)   // returns true, best == &values[1]
//   *best = 0;                    // values is now {3, 0, 4, 9}
//
// out is the address of the caller's pointer: *out = ... re-points it.
bool point_at_max(std::vector<int> &values, int **out) {
    throw "TODO";
}
