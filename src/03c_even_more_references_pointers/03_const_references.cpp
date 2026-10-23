// === Lesson: const references ================================================
//
// const& is the usual way to pass something big that the function only reads.
// Like &, it's a second name for the caller's box, so nothing is copied. const
// adds a promise: the function won't change the box through this name.
//
//     int count_spaces(const std::string &text);    // reads the caller's string in place
//
// Inside, the compiler holds you to it. Anything that could write is an error:
//
//     text += "!";                         // error: text is const
//     text[0] = 'X';                       // error
//     std::string &t = text;               // error: a plain & could write
//     const std::string &t = text;         // fine
//
// The elements of a const vector are const too. for (int x : v) copies each
// element, which is fine for ints, and for (const std::string &s : words) reads
// each string without copying it.
//
// Unlike a plain &, a const& also accepts values that aren't variables. The
// compiler makes a temporary box that lives until the end of the statement:
//
//     count_spaces("a b c");                   // a literal
//     count_spaces(first + " " + last);        // the result of an expression
//
// Which arguments each kind of parameter accepts:
//
//                                   by value     &       const&
//     a variable                      yes       yes       yes
//     a const variable                yes       no        yes
//     a literal like 5 or "hi"        yes       no        yes
//     an expression like x + 1        yes       no        yes
//
// Pointers follow the same rule. A const int* can point at any int, but an int*
// can't point at a const int, since writing through it would break the promise:
//
//     const int k = 2;
//     int *p = &k;              // error
//     const int *q = &k;        // fine
//
// A reference or pointer you hand back into a const& parameter must be const
// too, or the caller could write through it:
//
//     const std::string *find_empty(const std::vector<std::string> &words);
//
// const& doesn't freeze the box. Code holding a plain & or the variable itself
// can still change it, even during the call (aliasing, in 02_pass_by_reference).
//
// Read more: https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/
//            https://www.learncpp.com/cpp-tutorial/pointers-and-const/
//
// === Exercise: const references ==============================================
// Answer the trace, then implement the three functions. Each one only reads
// its inputs, so the tests call them with literals and temporaries as well as
// variables.
//
// ./grade 03c_even_more_references_pointers/03_const_references

#include <cstddef>
#include <string>
#include <vector>

// Trace 5. Which of these calls compile? Return their numbers in order, like {2, 4}.
//
//     void a(int n);
//     void b(int &n);
//     void c(const int &n);
//     void d(int *p);
//     void e(const int *p);
//
//     int x = 1;
//     const int k = 2;
//
//     (1) a(k)     (2) b(k)     (3) c(x + 1)     (4) b(x + 1)
//     (5) d(&k)    (6) e(&k)    (7) e(&x)        (8) c(5)
std::vector<int> trace_5() {
    throw "TODO";
}

// Return true when text reads the same forwards and backwards.
// Every character counts, spaces included, and case matters: "Aa" is not a palindrome.
// "" and single characters are palindromes.
//
// Example:
//   is_palindrome("racecar") is true
//   is_palindrome("abca") is false
//   is_palindrome(std::string("ab") + "ba") is true    // a temporary
//
// text is const&, so a literal or the result of + can be passed straight in.
bool is_palindrome(const std::string &text) {
    throw "TODO";
}

// Return a reference to the value that appears most often in values.
// Refer to that value's first occurrence.
// On a tie in count, pick the value whose first occurrence comes first.
// values is never empty.
//
// Example:
//   values = {4, 1, 4, 2, 1}
//   const int &m = most_common(values);
//   // 4 and 1 both appear twice, and 4 comes first, so &m == &values[0]
//
// Returns a const reference because values is const: the caller reads the element, not a copy.
const int &most_common(const std::vector<int> &values) {
    throw "TODO";
}

// Return a pointer to the first word that starts with prefix, or nullptr if none does.
// A word equal to prefix counts. An empty prefix matches every word.
//
// Example:
//   words = {"banana", "apple", "apricot"}
//   find_by_prefix(words, "ap") == &words[1]
//   find_by_prefix(words, "cherry") is nullptr
//   find_by_prefix(words, "") == &words[0]
//
// Returns const std::string*: it points into a const vector, so the caller may only read.
const std::string *find_by_prefix(const std::vector<std::string> &words, const std::string &prefix) {
    throw "TODO";
}
