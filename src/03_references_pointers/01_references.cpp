// === Lesson: References ======================================================
//
// Passing a variable to a function copies it, even a std::vector or a
// std::string. (JavaScript and Python share objects between caller and callee;
// C++ only does that when you ask for a reference.)
//
// A reference is a second name for an existing variable. It must be bound when
// it's created, it can never be rebound to another variable, and there is no
// null reference:
//
//     int score = 10;
//     int& alias = score;    // alias is score, under another name
//     alias += 5;            // score is now 15
//
// Parameters are where references earn their keep:
//
//     void clear_all(std::vector<int> v);        // gets a copy: caller sees nothing
//     void clear_all(std::vector<int>& v);       // works on the caller's vector
//     int total(const std::vector<int>& v);      // no copy, and can't modify it
//
// A non-const reference can't bind to a temporary: with `void bump(int& n)`,
// bump(5) doesn't compile. A const& can, so total({1, 2, 3}) works.
//
// The same choice exists in a range-for loop:
//
//     for (std::string s : names) s += "!";      // edits copies: names unchanged
//     for (std::string& s : names) s += "!";     // edits the strings in names
//
// Out parameters. A function returns one value, but it can also write results
// into references the caller passes in:
//
//     void split_seconds(int total, int& minutes, int& seconds) {
//         minutes = total / 60;
//         seconds = total % 60;
//     }
//     int m = 0, s = 0;
//     split_seconds(135, m, s);      // m == 2, s == 15
//
// Returning a reference gives the caller access to an object that outlives the
// call, such as an element of a vector the caller passed in:
//
//     int& first(std::vector<int>& v) { return v[0]; }
//
//     first(v) = 99;                 // assigns to v[0]
//     int copy = first(v);           // a copy: changing it won't touch v
//     int& same = first(v);          // another name for v[0]
//
// Never return a reference to a local variable. It's destroyed when the function
// returns, and the caller is left holding a dangling reference.
//
// Two reference parameters can name the same variable, as in f(x, x), so don't
// write code that assumes they're different objects.
//
// Read more: https://www.learncpp.com/cpp-tutorial/lvalue-references/
//            https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/
//
// === Exercise: References ====================================================
// Implement the four functions below.
//
// ./grade 03_references_pointers/01_references

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
