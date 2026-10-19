// === Lesson: Functions =======================================================
//
// A function names its return type and the types of its parameters. Each
// parameter is a copy of the argument (pass by value) unless it's a reference.
// Unlike JavaScript and Python, a function must be declared above the code
// that calls it: the compiler reads the file top to bottom.
//
// Overloading: several functions may share a name if their parameter lists
// differ. The compiler picks the best match for the argument types:
//
//     double area(double radius) { return 3.14159 * radius * radius; }
//     double area(double width, double height) { return width * height; }
//     area(2.0);         // the first one
//     area(2.0, 3.0);    // the second one
//
// The return type alone can't tell overloads apart. When no overload is the
// clear best match, the call doesn't compile: with f(int, int) and
// f(double, double), the call f(1, 2.5) is "ambiguous".
//
// Default arguments fill in trailing parameters the caller leaves out. Only
// the last parameters can have them:
//
//     std::string greet(const std::string& name, const std::string& word = "Hello") {
//         return word + ", " + name + "!";
//     }
//     greet("Ada");          // "Hello, Ada!"
//     greet("Ada", "Hi");    // "Hi, Ada!"
//
// (const std::string& reads the caller's string without copying it.
// References get their own module soon.)
//
// Recursion: a function calling itself on a smaller input, with a base case
// that stops it. Without a reachable base case it recurses until the stack
// runs out, which the grader reports as a stack overflow.
//
//     void countdown(int n) {
//         if (n == 0) {                  // base case
//             std::cout << "liftoff\n";
//             return;
//         }
//         std::cout << n << ' ';
//         countdown(n - 1);              // a smaller problem
//     }
//
// A static local variable is initialized once, not on every call, and keeps
// its value between calls: a global that only one function can see.
//
//     bool same_as_last_time(int value) {
//         static int last = 0;
//         bool same = (value == last);
//         last = value;
//         return same;
//     }
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-function-overloading/
//            https://www.learncpp.com/cpp-tutorial/static-local-variables/
//
// === Exercise: Functions =====================================================
// Overloading, default arguments, recursion, and a static local variable.
//
// ./grade 01_basics/04_functions

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
