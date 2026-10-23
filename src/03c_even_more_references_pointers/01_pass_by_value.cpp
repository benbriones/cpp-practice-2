// === Lesson: Passing by value ================================================
//
// A parameter that isn't a reference is a brand-new box. It's filled with a
// copy of the argument when the call starts and destroyed at the closing brace:
//
//     void bump(int n) { n += 1; }
//
//     int score = 10;
//     bump(score);
//
//          caller                 bump
//     score [ 10 ]            n [ 10 ] -> [ 11 ]      n is destroyed at the }
//
// score is still 10. bump changed its own box, and nothing connects that box
// back to score.
//
// That holds for every type, not only int. A std::string or std::vector
// parameter is a full copy, with its own characters or elements:
//
//     void wipe(std::vector<int> v) { v.clear(); }
//
//     std::vector<int> values{1, 2, 3};
//     wipe(values);             // values is still {1, 2, 3}
//
// Inside wipe, &v[0] != &values[0]: two vectors, two sets of elements. Even a
// for (int &x : v) loop inside wipe only reaches the copy's elements.
//
// So a by-value parameter is yours to change. Use it as a scratch variable:
//
//     int count_digits(int n) {
//         int digits = 1;
//         while (n >= 10) { n /= 10; ++digits; }     // wears n down; the caller's int is safe
//         return digits;
//     }
//
// or as the starting point of a new result. Change the copy, then return it:
//
//     std::string with_bang(std::string word) {
//         word += "!";
//         return word;
//     }
//
//     std::string name = "hi";
//     std::string loud = with_bang(name);       // name is "hi", loud is "hi!"
//     name = with_bang(name);                   // the caller opts in: name is "hi!"
//
// The return value is a copy going the other way. If nobody stores it, it's
// thrown away, so with_bang(name); on a line of its own changes nothing.
//
// When by value is the right choice:
//
//     small types: int, double, char, bool, pointers     cheap to copy
//     you'd copy it anyway, to change and return          std::string, std::vector
//
// Otherwise, copying a big string or vector only to read it is wasted work. The
// next two exercises cover & and const&, which skip the copy.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/
//            https://www.learncpp.com/cpp-tutorial/passing-stdvector/
//
// === Exercise: Passing by value ==============================================
// Predict the two traces on paper first, then implement the three functions.
// Each one takes its input by value, so it already owns a copy it can change.
//
// ./grade 03c_even_more_references_pointers/01_pass_by_value

#include <cctype>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

// Trace 1. What are a and b at the end? Return {a, b}.
//
//     int twice(int n) { n *= 2; return n; }
//
//     int a = 5;
//     int b = twice(a);
//     twice(b);
//     a = twice(a) + 1;
std::pair<int, int> trace_1() {
    throw "TODO";
}

// Trace 2. What does words hold at the end?
//
//     void shout_all(std::vector<std::string> words) {
//         for (std::string &w : words) w += "!";
//     }
//     std::vector<std::string> shouted(std::vector<std::string> words) {
//         for (std::string &w : words) w += "!";
//         return words;
//     }
//
//     std::vector<std::string> words{"hi", "yo"};
//     shout_all(words);
//     std::vector<std::string> louder = shouted(words);
//     words[1] = louder[0];
std::vector<std::string> trace_2() {
    throw "TODO";
}

// Return how many steps it takes n to reach 1.
// Each step: if n is even, halve it; if it's odd, make it 3 * n + 1.
// n is at least 1, and 1 itself takes 0 steps.
//
// Example:
//   collatz_steps(1) is 0
//   collatz_steps(6) is 8     // 6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
//   int start = 6;
//   collatz_steps(start);     // start is still 6
//
// n is a copy, so wear it down directly: no second variable needed for it.
int collatz_steps(int n) {
    throw "TODO";
}

// Return text with the first character of every word in upper case.
// Words are separated by spaces, and there may be several spaces in a row.
// Leave every other character as it is, including the rest of each word.
//
// Example:
//   capitalize_words("hello big world") is "Hello Big World"
//   capitalize_words("  mIxEd  case") is "  MIxEd  Case"
//   std::string title = "dune";
//   capitalize_words(title);  // title is still "dune"
//
// text is your own copy: change its characters in place, then return it.
std::string capitalize_words(std::string text) {
    throw "TODO";
}

// Return values with each element replaced by the sum of itself and every element before it.
//
// Example:
//   running_totals({1, 2, 3, 4}) is {1, 3, 6, 10}
//   running_totals({5, -5, 2}) is {5, 0, 2}
//   running_totals({}) is {}
//
// values is your own copy, so build the answer right inside it.
std::vector<int> running_totals(std::vector<int> values) {
    throw "TODO";
}
