// Exercise: References
// Implement the four functions below. A reference parameter (int&) is a
// second name for the caller's variable, so changes you make are visible to
// the caller:
//
//   void bump(int& n) { ++n; }      int x = 1;  bump(x);   // x is now 2
//
// A function can also return a reference, which lets the caller assign
// through the result:  largest(v) = 0;
//
// Grade: grade 03_references_pointers/01_references

#include <vector>

// Exchange the values of a and b.
void swap_ints(int& a, int& b) {
    throw "TODO";
}

// Double every element of values, in place.
void double_all(std::vector<int>& values) {
    throw "TODO";
}

// Write the smallest element into lo_out and the largest into hi_out.
// values is never empty. Returning two results through references is
// called using "out parameters".
void min_max(const std::vector<int>& values, int& lo_out, int& hi_out) {
    throw "TODO";
}

// A reference to the largest element (the first one, on ties), so callers can
// change it in place. values is never empty.
int& largest(std::vector<int>& values) {
    throw "TODO";
}
