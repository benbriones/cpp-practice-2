// === Lesson: Numbers and arithmetic ==========================================
//
// The everyday number types:
//
//     int        whole numbers, about ±2.1 billion (32 bits on every common platform)
//     long long  whole numbers, about ±9.2 × 10^18 (64 bits)
//     double     decimals, about 15-16 significant digits
//
//     int count = 3;
//     double price = 4.99;
//     long long big = 9'000'000'000;   // ' separates digits, for readability
//     auto n = 42;                     // auto takes its type from the value: int
//
// Arithmetic happens in the type of its operands. Only after that is the result
// converted to the type of the variable you store it in:
//
//     int a = 7, b = 2;
//     double x = a / b;                        // 3.0: int / int is 3, then stored
//     double y = static_cast<double>(a) / b;   // 3.5: one double operand is enough
//     double z = 9 / 5;                        // 1.0, but 9.0 / 5 is 1.8
//
// When an int meets a double in one operation, the int is converted to double
// first. static_cast<T>(value) asks for a conversion explicitly.
//
// Integer / rounds toward zero, so % takes the sign of the left operand:
//
//     -7 / 2 == -3      -7 % 2 == -1      // so `n % 2 == 1` misses negative odds
//
// Overflow: an int can't go past std::numeric_limits<int>::max(), which is
// 2'147'483'647. Going past it with a signed type is undefined behavior: the
// program may print garbage, crash or seem fine, and the grader's sanitizer
// reports it. Widen before the operation that overflows, not after it:
//
//     int ms_per_day = 86'400'000;
//     long long bad  = ms_per_day * 30;                          // overflows as int
//     long long good = static_cast<long long>(ms_per_day) * 30;  // done in long long
//
// Doubles are approximate: 0.1 + 0.2 != 0.3 (it's 0.30000000000000004), so
// compare decimals with a tolerance, not ==. <cmath> has std::abs, std::sqrt,
// std::pow and std::round.
//
// Read more: https://www.learncpp.com/cpp-tutorial/arithmetic-operators/
//            https://www.learncpp.com/cpp-tutorial/arithmetic-conversions/
//
// === Exercise: Numbers and arithmetic ========================================
// Implement the four functions below.
//
// ./grade 01_basics/01_arithmetic

// Average of a and b: average(1, 2) == 1.5. Must work for values near the int limit.
double average(int a, int b) {
    throw "TODO";
}

// Fahrenheit = celsius × 9/5 + 32.
double celsius_to_fahrenheit(double celsius) {
    throw "TODO";
}

// The last digit of n, always non-negative: last_digit(1234) == 4, last_digit(-57) == 7.
int last_digit(int n) {
    throw "TODO";
}

// Seconds in `years` years of 365 days. Large inputs don't fit in an int.
long long seconds_in_years(int years) {
    throw "TODO";
}
