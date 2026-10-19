// === Lesson: C-style arrays and pointer arithmetic ===========================
//
// Before std::vector and std::array there were built-in arrays: a fixed number
// of elements stored side by side, sized at compile time.
//
//     int values[5] = {7, 3, 8, 5, 4};
//     int zeros[100] = {};          // {} zero-fills; without it, locals hold garbage
//     std::size(values)             // 5 (<iterator>): only where the array is declared
//
// Decay. An array can't be passed or returned by value. Pass one to a function
// and what arrives is a pointer to its first element; the size is lost, so it
// has to travel as a separate argument. `int values[]` in a parameter list is
// just another spelling of `int* values`, and sizeof there gives the size of a
// pointer (clang warns about it).
//
// Pointer arithmetic. Adding n to a pointer moves it n *elements*, not bytes,
// and p[i] is defined as *(p + i):
//
//     int* p = values;              // same as &values[0]
//     *(p + 2)                      // 8, same as p[2] and values[2]
//     p + 5                         // one past the end: fine to compare against,
//                                   // never to dereference
//     (p + 5) - p                   // 5: subtracting pointers counts elements
//
// Half-open ranges. A range can also be given as two pointers, begin and end,
// where end points one past the last element: [begin, end). An empty range is
// begin == end, the loop needs no index, and this is exactly the convention of
// begin()/end() on every standard container:
//
//     void fill(int* begin, int* end, int value) {
//         for (int* p = begin; p != end; ++p) {
//             *p = value;
//         }
//     }
//     int scores[4];
//     fill(scores, scores + 4, 7);  // {7, 7, 7, 7}
//     fill(scores + 1, scores + 3, 0);   // {7, 0, 0, 7}
//
// Returning a pointer to an element gives the caller access to the real
// element, so they can read or change it. nullptr is the usual "not found".
// A const int* can be read through but not written through.
//
// Reading or writing outside the array is undefined behavior. Nothing checks it
// in an ordinary build; here the address sanitizer reports it.
//
// Read more: https://www.learncpp.com/cpp-tutorial/c-style-array-decay/
//            https://www.learncpp.com/cpp-tutorial/pointer-arithmetic-and-subscripting/
//
// === Exercise: C-style arrays ================================================
// Implement the four functions below.
//
// ./grade 10_memory/01_c_arrays

// Pointer to the first even element, or nullptr if there is none.
int* find_first_even(int values[], int count) {
    throw "TODO";
}

int sum_array(const int* values, int count) {
    throw "TODO";
}

// Reverse the first `count` elements in place.
void reverse_array(int* values, int count) {
    throw "TODO";
}

// How many elements of the half-open range [begin, end) lie between lo and hi
// inclusive. `end` points one past the last element, like a vector's end().
// Walk the range with a pointer (++p) rather than an index.
int count_in_range(const int* begin, const int* end, int lo, int hi) {
    throw "TODO";
}
