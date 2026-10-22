// === Lesson: nullptr and "not found" =========================================
//
// nullptr is a pointer value that points at no box at all:
//
//     int *p = nullptr;         p --> (nothing)
//
// Following it is undefined behavior. Here the sanitizers stop the program and
// report "load of null pointer" (reading) or "store to null pointer" (writing);
// without them the program may crash, or quietly read garbage. A local pointer that was never set is worse:
// it holds leftover bits that look like a real address. Give every pointer a
// value, and use nullptr when you don't have one yet.
//
// A null pointer converts to false and any other pointer to true. That tests
// the pointer, not the int it points at:
//
//     int zero = 0;
//     int *p = &zero;
//     if (p)  { ... }           // runs: p points somewhere
//     if (*p) { ... }           // doesn't run: the int is 0
//
// Check first, return early, then do the real work. After the guard, *s is safe:
//
//     int length_or_zero(const std::string *s) {
//         if (s == nullptr) return 0;
//         return static_cast<int>(s->size());     // s->size() means (*s).size()
//     }
//
// -> calls a member through a pointer. *s.size() doesn't compile, because .
// binds tighter than *; you'd need (*s).size(), and -> is the short form.
//
// nullptr is the natural "not found" for a search that hands back the element
// itself, so the caller can read it or change it in place:
//
//     std::string *find_long(std::vector<std::string> &words) {
//         for (std::string &w : words) {
//             if (w.size() > 10) return &w;       // w is the element, so &w is its address
//         }
//         return nullptr;
//     }
//
//     if (std::string *w = find_long(words)) {    // w only exists inside the if
//         *w = "(too long)";
//     }
//
// A std::optional<std::string> would hand back a copy; a pointer hands back
// the original. Take a const vector and return const T* when the caller should
// only read; take a non-const vector and return T* when they may write.
//
// Try it: add an int main() that dereferences a nullptr, run grade --run 03b/03,
// and read the report so you recognize it next time.
//
// Read more: https://www.learncpp.com/cpp-tutorial/null-pointers/
//            https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
//
// === Exercise: nullptr and "not found" =======================================
// Predict the trace, then implement the five functions. Every function that
// takes a pointer may be handed nullptr unless its comment says otherwise.
//
// ./grade 03b_more_references_pointers/03_nullptr

#include <string>
#include <vector>

// Trace 5. Which of these conditions are true? Return their numbers in order, like {2, 4}.
//
//     int zero = 0;
//     int one = 1;
//     int *p = &zero;
//     int *q = nullptr;
//     int *s = &one;
//
//     (1) p    (2) *p    (3) q    (4) q == nullptr    (5) s && *s == 1    (6) p == s
std::vector<int> trace_5() {
    throw "TODO";
}

// Return *p, or fallback when p is nullptr.
//
// Example:
//   int x = 42;
//   int zero = 0;
//   value_or(&x, -1) is 42
//   value_or(nullptr, -1) is -1
//   value_or(&zero, -1) is 0
//
// A pointer to 0 is still a real pointer, so it isn't treated as missing.
int value_or(const int *p, int fallback) {
    throw "TODO";
}

// Return a pointer to the first even element of values.
// If there isn't one (including when values is empty), return nullptr.
// 0 and negatives like -4 count as even.
//
// Example:
//   values = {7, 3, 8, 5, 4}
//   find_first_even(values) == &values[2]   // the 8
//   odds = {1, 3, 5}
//   find_first_even(odds) is nullptr
//
// Returns a const int*, so the caller can read the element but not change it.
const int *find_first_even(const std::vector<int> &values) {
    throw "TODO";
}

// Return a pointer to the last element equal to target.
// If no element equals target, return nullptr.
//
// Example:
//   values = {5, 1, 5, 2}
//   find_last(values, 5) == &values[2]   // the second 5
//   find_last(values, 9) is nullptr
//   *find_last(values, 5) = 0;           // values is now {5, 1, 0, 2}
//
// The caller may change the element through the returned pointer.
int *find_last(std::vector<int> &values, int target) {
    throw "TODO";
}

// Return a pointer to the first name equal to wanted, or nullptr if none is.
// Only exact matches count: "ada" doesn't match "Ada", and neither does "Ad".
//
// Example:
//   names = {"Ada", "Bob", "Cy"}
//   find_name(names, "Bob") == &names[1]
//   find_name(names, "Dee") is nullptr
//   *find_name(names, "Bob") = "Robert";   // names is now {"Ada", "Robert", "Cy"}
//
// The caller may rename through the returned pointer.
std::string *find_name(std::vector<std::string> &names, const std::string &wanted) {
    throw "TODO";
}

// Return whichever of a and b points at the larger value.
// If both values are equal, return a.
// If one of them is nullptr, return the other. If both are, return nullptr.
//
// Example:
//   int x = 3;
//   int y = 8;
//   max_of(&x, &y) == &y
//   max_of(&x, nullptr) == &x
//   max_of(nullptr, nullptr) is nullptr
//
// nullptr means "no value", so any real pointer beats it, even one to a negative.
const int *max_of(const int *a, const int *b) {
    throw "TODO";
}
