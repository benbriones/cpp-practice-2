// === Lesson: Pointers and references as parameters ===========================
//
// Unless the parameter is a reference, it gets a copy of the argument, and that
// includes pointers:
//
//     void by_value(int n)     { n *= 2; }
//     void by_pointer(int* n)  { *n *= 2; }
//     void by_ref(int& n)      { n *= 2; }
//
//     int score = 10;
//     by_value(score);          score [ 10 ]     n [ 20 ]        n is thrown away at return
//     by_pointer(&score);       score [ 20 ] <-- n [ &score ]   *n reaches back to score
//     by_ref(score);            score, n [ 40 ]                 one box, two names
//
// by_pointer gets a copy of the address, but a copy of an address still leads
// to the original box, so *n changes score. What it can't change is which box
// the caller's pointer points at: n = &other only moves the function's own
// copy. To re-point the caller's pointer, take the pointer by reference. Read
// the type right to left:
//
//     void clear(int*& p) { p = nullptr; }      // int*&: reference to pointer to int
//
//     int* cursor = &score;
//     clear(cursor);            // cursor is now nullptr
//
// Out parameters deliver extra results. Pick the form by asking whether the
// caller always wants one:
//
//     void split_seconds(int total, int& minutes, int& seconds);     // always written
//     void range(const std::vector<int>& v, int* min_out, int* max_out);
//     range(v, &lo, nullptr);   // a pointer lets the caller opt out with nullptr
//
// Check each optional out pointer before writing through it. Another common
// shape is "return whether it worked, write the answer through an out
// parameter", leaving the out parameter alone on failure so the caller's old
// value survives:
//
//     bool parse_yes_no(const std::string& text, bool& answer) {
//         if (text == "yes") { answer = true; return true; }
//         if (text == "no") { answer = false; return true; }
//         return false;
//     }
//
// Choosing a parameter type:
//
//     small and read-only: int, double, char          by value
//     large and read-only: std::string, std::vector   const&
//     the function changes it                         &
//     optional: the caller may have nothing to pass   pointer, nullptr when absent
//
// Read more: https://www.learncpp.com/cpp-tutorial/pass-by-address/
//            https://www.learncpp.com/cpp-tutorial/in-and-out-parameters/
//
// === Exercise: Pointers and references as parameters =========================
// Predict the trace, then implement the four functions.
//
// ./grade 03b_more_references_pointers/04_parameters

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// Trace 6. What is x at the end?
//
//     void add_one(int n)        { n += 1; }
//     void add_ten(int* n)       { *n += 10; }
//     void add_hundred(int& n)   { n += 100; }
//     void misdirect(int* n)     { int other = 0; n = &other; *n += 1000; }
//
//     int x = 0;
//     add_one(x);
//     add_ten(&x);
//     add_hundred(x);
//     misdirect(&x);
int trace_6() { return 110; }

// If c is a digit, write its value into digit ('7' gives 7) and return true.
// Otherwise return false and leave digit alone.
bool parse_digit(char c, int& digit) {
    if (!std::isdigit(c)) return false;

    int converted = c - '0';  // converts to an int

    digit = converted;

    return true;
}

// Split full at its first space: "Ada Lovelace" gives first "Ada" and last
// "Lovelace". With no space, first is all of full and last is "".
void split_name(const std::string& full, std::string& first, std::string& last) {
    std::size_t spaceIndex = full.find(" ");

    std::cout << "spaceIndex for:" << full << " " << spaceIndex;

    if (spaceIndex == std::string::npos) {
        first = full;
        last = "";
        return;
    }

    first = full.substr(0, spaceIndex);
    last = full.substr(spaceIndex + 1);
    return;
}

// Return the sum of values, and write the smallest into *min_out and the largest
// into *max_out, skipping either one that is nullptr. If values is empty, return
// 0 and write nothing.
int sum_with_extremes(const std::vector<int>& values, int* min_out, int* max_out) {
    if (values.empty()) return 0;

    int sum = 0;
    int currMin = values[0];
    int currMax = values[0];

    for (int v : values) {
        if (!v) continue;

        sum += v;

        if (v > currMax) {
            currMax = v;
        }
        if (v < currMin) {
            currMin = v;
        };
    }

    if (min_out != nullptr) {
        *min_out = currMin;
    }
    if (max_out != nullptr) {
        *max_out = currMax;
    }

    return sum;
}

// Make best point at candidate when best is nullptr or *candidate > *best.
// candidate is never null.
void keep_larger(int*& best, int* candidate) {
    if (best == nullptr || *candidate > *best) {
        best = candidate;
    }
 }
