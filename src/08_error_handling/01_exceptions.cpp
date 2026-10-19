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

// Parse a positive whole number: digits only, no sign, no spaces.
// Throws std::invalid_argument if text is empty or has any non-digit, and
// std::out_of_range if the value is 0 or too big for an int.
// (std::stoi throws both of these itself, but it also accepts "12abc" and " 12",
// so check the characters first.)
int parse_positive(const std::string& text) {
    throw "TODO";
}

// values[index], but throws std::out_of_range if index is outside the vector.
// Its what() must read exactly: "index 5 out of range for size 3"
int checked_at(const std::vector<int>& values, int index) {
    throw "TODO";
}

// a / b, but throws std::domain_error("division by zero") when b is 0.
double safe_divide(double a, double b) {
    throw "TODO";
}

// The sum of the texts that parse_positive accepts; the rest are skipped.
int sum_valid(const std::vector<std::string>& texts) {
    throw "TODO";
}

// Report what parse_positive does with text: "ok: 42", "invalid argument", or
// "out of range". Use one catch clause per exception type.
std::string try_parse(const std::string& text) {
    throw "TODO";
}
