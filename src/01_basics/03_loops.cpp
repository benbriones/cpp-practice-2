// === Lesson: Loops ===========================================================
//
// A while loop checks its condition before each pass:
//
//     double balance = 100.0;
//     int years = 0;
//     while (balance < 200.0) {       // years to double your money at 7%
//         balance *= 1.07;
//         ++years;
//     }
//
// A for loop puts the setup, condition and step on one line, which suits
// counting. The variable i exists only inside the loop:
//
//     for (int i = 1; i <= 5; ++i) {
//         std::cout << i * i << ' ';  // 1 4 9 16 25
//     }
//
// A do-while loop checks after each pass, so the body runs at least once:
//
//     char answer = ' ';
//     do {
//         std::cout << "Continue? (y/n) ";
//         std::cin >> answer;
//     } while (answer != 'y' && answer != 'n');
//
// break leaves the loop at once, and continue skips to the next pass. A
// function can also return from inside a loop as soon as it knows the answer.
//
// C++ has no `a, b = b, a + b`. To update two variables from each other's old
// values, keep one in a temporary:
//
//     int prev = 0, curr = 1;         // Fibonacci numbers
//     for (int i = 0; i < 10; ++i) {
//         int next = prev + curr;
//         prev = curr;
//         curr = next;
//     }
//
// Watch the arithmetic in a loop condition. This counts the perfect squares up
// to n, but for n near the int limit, i * i overflows (undefined behavior)
// before the comparison can end the loop:
//
//     for (int i = 1; i * i <= n; ++i) ++count;        // breaks near 2^31
//     for (long long i = 1; i * i <= n; ++i) ++count;  // fine: 64-bit math
//
// A loop that never ends shows up in the grader as a timeout. Make sure every
// pass moves toward the exit condition.
//
// Read more: https://www.learncpp.com/cpp-tutorial/for-statements/
//            https://www.learncpp.com/cpp-tutorial/break-and-continue/
//
// === Exercise: Loops =========================================================
// Implement the four functions below using for, while, or do-while loops.
//
// ./grade 01_basics/03_loops

// Sum of the decimal digits of n, ignoring its sign: sum_of_digits(-123) == 6.
int sum_of_digits(int n) {
    throw "TODO";
}

// True if n is prime. Numbers below 2 are not prime.
// Only test divisors up to the square root of n; the tests use large primes.
bool is_prime(int n) {
    throw "TODO";
}

// Greatest common divisor using Euclid's algorithm: repeatedly replace
// (a, b) with (b, a % b) until b is 0. Inputs are non-negative and not both 0.
int gcd(int a, int b) {
    throw "TODO";
}

// Collatz: if n is even halve it, otherwise make it 3n + 1. Count the steps
// until n reaches 1. collatz_steps(1) == 0, collatz_steps(6) == 8.
int collatz_steps(int n) {
    throw "TODO";
}
