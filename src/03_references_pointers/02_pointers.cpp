// Exercise: Pointers
// A pointer holds an address. &x takes the address of x, *p reaches the value
// a pointer points at, and nullptr means "points at nothing". Following a null
// pointer is undefined behavior, so check before you dereference.
//
//   int x = 5;  int* p = &x;  *p = 7;   // x is now 7
//
// A `const int*` can read the value it points at but not change it.
//
// Grade: grade 03_references_pointers/02_pointers

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
