// === Lesson: Conditions and operators ========================================
//
// if / else if / else runs the first branch whose condition is true. Order the
// branches so the most specific case comes first:
//
//     if (n % 15 == 0) {          // must come first: 15 is also divisible by 3
//         return "FizzBuzz";
//     } else if (n % 3 == 0) {
//         return "Fizz";
//     } else if (n % 5 == 0) {
//         return "Buzz";
//     } else {
//         return std::to_string(n);
//     }
//
// Comparisons: == != < <= > >=. Logic: && (and), || (or), ! (not). && and ||
// short-circuit: the right side runs only if it can still change the answer,
// so the left side can guard the right:
//
//     if (count != 0 && total / count > 10) { ... }   // never divides by zero
//
// && binds tighter than ||, so a || b && c means a || (b && c). Add parentheses
// whenever you mix them. And 0 < x < 10 doesn't mean what it does in math or
// Python: it's (0 < x) < 10, which is always true. Clang rejects it; write
// 0 < x && x < 10.
//
// The ternary operator picks one of two values: condition ? if_true : if_false.
//
//     std::string noun = (n == 1) ? "item" : "items";
//
// switch jumps to the case label equal to an integer, char or enum value (not
// a string). Execution falls through into the next case unless you break or
// return, which lets several labels share one body:
//
//     switch (day) {                  // 1 = Monday ... 7 = Sunday
//         case 6:
//         case 7:
//             return "weekend";
//         case 1: case 2: case 3: case 4: case 5:
//             return "weekday";
//         default:                    // any value without a label
//             return "not a day";
//     }
//
// A forgotten break is a classic bug: the next case's code runs too. Code that
// falls through on purpose after doing some work is marked [[fallthrough]];.
//
// Handling invalid input first, with an early return, keeps the rest flat:
// if (...) { return ...; } and then the normal case without an else.
//
// Read more: https://www.learncpp.com/cpp-tutorial/logical-operators/
//            https://www.learncpp.com/cpp-tutorial/switch-statement-basics/
//
// === Exercise: Conditions and operators ======================================
// Implement the four functions below with if/else, switch, and the logical
// operators && || !.
//
// ./grade 01_basics/02_conditions

#include <string>

// Leap years are divisible by 4, except centuries, which must be divisible by 400.
// is_leap_year(2024) == true, is_leap_year(1900) == false, is_leap_year(2000) == true
bool is_leap_year(int year) {
    throw "TODO";
}

// Days in a month (1 = January). Return 0 for a month outside 1..12.
// Use a switch; several cases can share one body.
int days_in_month(int month, int year) {
    throw "TODO";
}

// 90+ → 'A', 80+ → 'B', 70+ → 'C', 60+ → 'D', otherwise 'F'.
// Scores outside 0..100 return '?'.
char letter_grade(int score) {
    throw "TODO";
}

// "equilateral", "isosceles", or "scalene". Return "invalid" if any side is not
// positive, or if the two shorter sides don't add up to more than the longest.
std::string classify_triangle(int a, int b, int c) {
    throw "TODO";
}
