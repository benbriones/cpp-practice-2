// Exercise: Conditions and operators
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
