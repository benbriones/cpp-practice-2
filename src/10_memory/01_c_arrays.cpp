// Exercise: C-style arrays
// Before std::vector there were raw arrays:  int values[5] = {7, 3, 8, 5, 4};
// Pass one to a function and it "decays" to a pointer to its first element,
// forgetting its size, so the size has to travel separately: f(values, 5).
// p[i] and *(p + i) mean the same thing.
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
