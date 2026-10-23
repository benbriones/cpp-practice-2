// === Lesson: Passing by reference ============================================
//
// A & parameter isn't a new box. It's a second name written on the caller's
// box, so every read and write goes straight to the caller's variable:
//
//     void bump(int &n) { n += 1; }
//
//     int score = 10;
//     bump(score);
//
//      score, n
//     +--------+
//     |   11   |            one box, two names: score is 11 when bump returns
//     +--------+
//
// That's how a function changes its caller's data: in place, as with
// std::vector<int> &v, or through out parameters that deliver extra results.
//
// A plain & needs a variable to name, so bump(5) and bump(score + 1) don't
// compile: there's no caller's box for the change to land in.
//
// Swapping is the classic case. Both names lead to the caller's boxes, and a
// local holds one value while the other is overwritten:
//
//     void swap_ints(int &a, int &b) { int old_a = a; a = b; b = old_a; }
//
// Aliasing. Two reference parameters can name the same box, and code that
// assumes they're different gets a surprise:
//
//     void add_twice(int &total, const int &step) { total += step; total += step; }
//
//     int x = 3;
//     add_twice(x, x);          // total and step are both x: x is 6, then 12, not 9
//
// const on step only stops add_twice from writing through that name. The box
// can still change through total. Copy what you need first (int s = step;), or
// take small inputs by value so there's nothing to alias.
//
// A reference into a vector you're growing is the worst case. When push_back
// runs out of room it moves every element to a new block, and every reference,
// pointer and range-for into the old block dangles:
//
//     void pad(std::vector<int> &v, int count) {          // v is never empty
//         const int &last = v.back();
//         for (int i = 0; i < count; ++i) v.push_back(last);   // last dangles after a regrow
//     }
//
// int last = v.back(); takes a copy that no regrow can touch. A range-for over a
// vector while you push onto that same vector has the same problem.
//
// Read more: https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/
//            https://www.learncpp.com/cpp-tutorial/stdvector-resizing-and-capacity/
//
// === Exercise: Passing by reference ==========================================
// Predict the two traces, then implement the three functions. Each one changes
// its caller's variables through reference parameters.
//
// ./grade 03c_even_more_references_pointers/02_pass_by_reference

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

// Trace 3. What are x and y at the end? Return {x, y}.
//
//     void transfer(int &from, int &to, int amount) { from -= amount; to += amount; }
//
//     int x = 10;
//     int y = 0;
//     transfer(x, y, 3); x is 7          y is 3
//     transfer(y, x, 1); x is 8          y is 2
//     transfer(x, x, 5); x is 8.    y is 2
std::pair<int, int> trace_3() { return {8, 2}; }

// Trace 4. What are x, y and z at the end? Return {x, y, z}.
//
//     void sum_into(int &total, const int &a, const int &b) { total = a; total += b; }
//
//     int x = 1;
//     int y = 2;
//     int z = 0;
//     sum_into(z, x, y);
//     sum_into(x, y, x);
//     sum_into(y, y, y);
std::vector<int> trace_4() { throw "TODO"; }

// Rearrange the values of a, b and c so that a <= b <= c.
//
// Example:
//   int x = 3;
//   int y = 1;
//   int z = 2;
//   sort3(x, y, z);   // x is now 1, y is 2, z is 3
//
// Each parameter is the caller's variable, so swapping values here swaps theirs.
void sort3(int &a, int &b, int &c) { throw "TODO"; }

// Remove the first word from text and write it into word, then return true.
// Words are separated by single spaces, and text never starts or ends with one.
// If text is empty, return false and leave both strings alone.
//
// Example:
//   std::string text = "to be or";
//   std::string word = "old";
//   pop_word(text, word)   // returns true, word is "to", text is "be or"
//   pop_word(text, word)   // returns true, word is "be", text is "or"
//   pop_word(text, word)   // returns true, word is "or", text is ""
//   pop_word(text, word)   // returns false, word is still "or"
//
// text is both an input and an output: the function reads it, then shortens it.
bool pop_word(std::string &text, std::string &word) {
    if (text == "") return false;

    // Get first word of text
    // Getting first space of text, and use text.substr(0, index)
    std::size_t firstSpaceIndex = text.find(" ");

    if (firstSpaceIndex == std::string::npos) {
        word = text;
        text = "";
        return true;
    }

    std::string firstWord = text.substr(0, firstSpaceIndex);

    // Remove word from text
    text = text.substr(firstSpaceIndex + 1, text.size() - firstSpaceIndex);

    // Set word to first word
    word = firstWord;
    return true;
}

// Append a copy of every element of src to the end of dest, in order.
// dest and src may be the very same vector. Then it ends up holding its elements twice.
//
// Example:
//   dest = {1, 2}, src = {3, 4}
//   append_copy(dest, src);    // dest is now {1, 2, 3, 4}, src is unchanged
//   v = {1, 2}
//   append_copy(v, v);         // v is now {1, 2, 1, 2}
//
// When they're the same vector, every push_back onto dest also grows src while you read it.
void append_copy(std::vector<int> &dest, const std::vector<int> &src) {
    std::vector<int> copyVec = src;


    for (int s : copyVec) {
        dest.push_back(s);
    }
}
