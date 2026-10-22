// === Lesson: Throwing and catching exceptions ================================
//
// throw reports an error the caller can't silently ignore. It leaves the current
// function immediately, and every function up the call chain, until a matching
// catch is found. Local objects are destroyed properly on the way out.
//
//     double ratio(int part, int whole) {
//         if (whole <= 0) {
//             throw std::invalid_argument("whole must be positive, got " +
//                                         std::to_string(whole));
//         }
//         return static_cast<double>(part) / whole;
//     }
//
//     try {
//         std::cout << ratio(3, 0) << '\n';         // throws: the print never runs
//     } catch (const std::invalid_argument& e) {
//         std::cout << "bad input: " << e.what() << '\n';
//     }
//
// C++ can throw any type, but use the standard exception classes from <stdexcept>
// or your own classes based on them. Each takes a message, which what() returns:
//
//     std::invalid_argument   the input is malformed
//     std::out_of_range       an index or value is outside what's allowed
//     std::domain_error       the input is outside where the math is defined
//     std::runtime_error      anything else that only shows up at run time
//
// The standard library throws these too: vector.at(i) throws std::out_of_range,
// and std::stoi throws std::invalid_argument when the text doesn't start with a
// number (after any spaces) and std::out_of_range when it doesn't fit in an int.
//
// Catch by const reference: const std::invalid_argument& e. Several catch clauses
// can follow one try, and the first one whose type matches wins. If nothing
// catches an exception, the program ends with std::terminate.
//
// Where you put the try decides what happens next. Inside a loop, it skips one
// bad item and carries on; around the whole loop, it stops at the first error.
//
// Coming from JavaScript or Python: the idea is the same, but you catch by type
// instead of inspecting the error, and there's no `finally`. C++ cleans up with
// destructors instead (module 11).
//
// You've already met one exception: every `throw "TODO";` in this course throws a
// string literal, which the grader catches and reports as "not implemented".
//
// Read more: https://www.learncpp.com/cpp-tutorial/basic-exception-handling/
//            https://www.learncpp.com/cpp-tutorial/exceptions-functions-and-stack-unwinding/
//
// === Exercise: Throwing and catching =========================================
// Implement the functions below.
//
// ./grade 08_error_handling/01_exceptions

#include <stdexcept>
#include <string>
#include <vector>

// Parse text as a positive whole number and return it.
// Accept digits only: no sign, no spaces.
// Throw std::invalid_argument if text is empty or has any non-digit.
// Throw std::out_of_range if the value is 0 or too big for an int.
//
// Example:
//   parse_positive("42") is 42, and parse_positive("007") is 7
//   parse_positive("12abc") and parse_positive(" 12") throw std::invalid_argument
//   parse_positive("0") and parse_positive("2147483648") throw std::out_of_range
//
// std::stoi throws both of these itself, but it also accepts "12abc" and " 12",
// so check the characters first.
int parse_positive(const std::string& text) {
    throw "TODO";
}

// Return values[index], checking the index first.
// Throw std::out_of_range if index is outside the vector (negative, or size or more).
// Its what() must read exactly: "index 5 out of range for size 3"
//
// Example:
//   values = {10, 20, 30}
//   checked_at(values, 2) is 30
//   checked_at(values, 5) throws, and what() is "index 5 out of range for size 3"
//   checked_at(values, -1) throws, and what() is "index -1 out of range for size 3"
int checked_at(const std::vector<int>& values, int index) {
    throw "TODO";
}

// Return a / b.
// Throw std::domain_error("division by zero") when b is 0.
//
// Example:
//   safe_divide(7, 2) is 3.5
//   safe_divide(-1, 4) is -0.25
//   safe_divide(1, 0) throws std::domain_error, and what() is "division by zero"
double safe_divide(double a, double b) {
    throw "TODO";
}

// Return the sum of the texts that parse_positive accepts.
// Skip every text that parse_positive throws on.
// If no text is valid, or texts is empty, return 0.
//
// Example:
//   sum_valid({"10", "abc", "0", "5", "99999999999", "-3", "20"}) is 35   // 10 + 5 + 20
//   sum_valid({"x", "y"}) is 0
//
// One bad text skips only itself; it doesn't stop the rest from being added.
int sum_valid(const std::vector<std::string>& texts) {
    throw "TODO";
}

// Return a report of what parse_positive does with text.
// If it parses, return "ok: " followed by the number, like "ok: 42".
// If it throws std::invalid_argument, return "invalid argument".
// If it throws std::out_of_range, return "out of range".
// Use one catch clause per exception type.
//
// Example:
//   try_parse("42") is "ok: 42"
//   try_parse("4x2") is "invalid argument"
//   try_parse("0") is "out of range"
//   try_parse("5000000000") is "out of range"
std::string try_parse(const std::string& text) {
    throw "TODO";
}
