// === Lesson: Pointers ========================================================
//
// A pointer is a variable that holds the address of another object. A reference
// is a permanent second name; a pointer can be null, can be pointed somewhere
// else later, and must be followed explicitly:
//
//     int score = 10;
//     int* p = &score;     // &score: the address of score
//     *p += 5;             // *p: the object p points at. score is now 15
//     p = nullptr;         // p points at nothing
//
// The same symbols mean different things in a type and in an expression:
//
//     int* p      in a declaration: p is a pointer to int
//     *p          in an expression: follow p to the int it points at
//     int& r      in a declaration: r is a reference to int
//     &x          in an expression: the address of x
//
// Following a null pointer (or one that was never set) is undefined behavior,
// so check first. A pointer converts to false when it's null:
//
//     if (p != nullptr) { ... }      // or just: if (p) { ... }
//
// Always initialize pointers: a local `int* p;` holds garbage, not nullptr.
//
// Precedence trap: *p++ means *(p++), which moves the pointer and leaves the
// value alone. To change the value, write ++*p or (*p)++.
//
// A pointer can point into a container. Writing through it changes the element,
// and comparing two pointers compares addresses, not values:
//
//     std::vector<int> v{1, 2, 3};
//     int* last = v.empty() ? nullptr : &v.back();
//     *last = 30;                       // v is now {1, 2, 30}
//     bool same = (last == &v[2]);      // true: the very same object
//
// A pointer into a vector dangles once the vector grows or is destroyed, so
// don't hold one across a push_back.
//
// const can apply to the pointed-at value or to the pointer itself. Read the
// declaration from right to left:
//
//     const int* a = &x;    // pointer to const int: *a = 1 doesn't compile
//     int* const b = &x;    // const pointer to int: b = &y doesn't compile
//
// Pointers often mean "maybe": a parameter the caller may pass as nullptr, or a
// result where nullptr means "not found". When a value must always be there,
// prefer a reference.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/
//            https://www.learncpp.com/cpp-tutorial/pointers-and-const/
//
// === Exercise: Pointers ======================================================
// Implement the five functions below.
//
// ./grade 03_references_pointers/02_pointers

#include <vector>

// Store value into the int that target points at. If target is nullptr, do nothing.
void set_if_not_null(int* target, int value) {
    throw "TODO";
}

// Exchange the two ints that a and b point at. Neither is null.
void swap_through(int* a, int* b) {
    throw "TODO";
}

// A pointer to the first element equal to target, or nullptr if there is none.
// The caller may write through the result to change the vector.
int* find_value(std::vector<int>& values, int target) {
    throw "TODO";
}

// If b is 0, return false and leave *result alone. Otherwise store a / b in
// *result and return true. result is never null.
bool safe_divide(int a, int b, int* result) {
    throw "TODO";
}

// Sum of the ints the pointers point at, skipping null pointers.
int sum_pointed(const std::vector<const int*>& pointers) {
    throw "TODO";
}
