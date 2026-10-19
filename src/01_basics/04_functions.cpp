// Exercise: Functions
// Overloading, default arguments, recursion, and a static local variable.
//
// Grade: grade 01_basics/04_functions

#include <string>

// Three overloads of max_of. Same name, different parameter lists: the
// compiler picks one from the argument types. Have the 3-int version reuse the
// 2-int one.
int max_of(int a, int b) {
    throw "TODO";
}

int max_of(int a, int b, int c) {
    throw "TODO";
}

double max_of(double a, double b) {
    throw "TODO";
}

// `text` repeated `times` times with `separator` between copies.
// repeat("ab") == "abab", repeat("ab", 3, "-") == "ab-ab-ab", times <= 0 gives "".
std::string repeat(const std::string& text, int times = 2, const std::string& separator = "") {
    throw "TODO";
}

// base raised to exponent (exponent >= 0), written recursively: no loops.
// Bonus: x^n = (x^(n/2))^2 needs far fewer calls than x * x^(n-1).
long long power(long long base, int exponent) {
    throw "TODO";
}

// Binary digits of n (n >= 0), recursively: to_binary(6) == "110", to_binary(0) == "0".
std::string to_binary(int n) {
    throw "TODO";
}

// Returns 1 on the first call, 2 on the next, and so on.
// A `static` local variable keeps its value between calls.
int next_ticket() {
    throw "TODO";
}
