// === Lesson: nullptr and "not found" =========================================
//
// nullptr is a pointer value that points at no box at all:
//
//     int* p = nullptr;         p --> (nothing)
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
//     int* p = &zero;
//     if (p)  { ... }           // runs: p points somewhere
//     if (*p) { ... }           // doesn't run: the int is 0
//
// Check first, return early, then do the real work. After the guard, *s is safe:
//
//     int length_or_zero(const std::string* s) {
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
//     std::string* find_long(std::vector<std::string>& words) {
//         for (std::string& w : words) {
//             if (w.size() > 10) return &w;       // w is the element, so &w is its address
//         }
//         return nullptr;
//     }
//
//     if (std::string* w = find_long(words)) {    // w only exists inside the if
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
//     int* p = &zero;
//     int* q = nullptr;
//     int* s = &one;
//
//     (1) p    (2) *p    (3) q    (4) q == nullptr    (5) s && *s == 1    (6) p == s
std::vector<int> trace_5() {
    throw "TODO";
}

// *p, or fallback when p is nullptr.
int value_or(const int* p, int fallback) {
    throw "TODO";
}

// A pointer to the first even element, or nullptr if there isn't one.
const int* find_first_even(const std::vector<int>& values) {
    throw "TODO";
}

// A pointer to the last element equal to target, or nullptr if there isn't one.
// The caller may change the element through it.
int* find_last(std::vector<int>& values, int target) {
    throw "TODO";
}

// A pointer to the first name equal to wanted, or nullptr. The caller may rename
// through it: *find_name(names, "Bob") = "Robert".
std::string* find_name(std::vector<std::string>& names, const std::string& wanted) {
    throw "TODO";
}

// Whichever of a and b points at the larger value (a on ties). If one of them is
// nullptr, return the other; if both are, return nullptr.
const int* max_of(const int* a, const int* b) {
    throw "TODO";
}
