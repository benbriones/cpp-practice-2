// Exercise: Throwing and catching
// throw reports an error the caller can't ignore; try/catch handles one.
// The standard exception types live in <stdexcept> and carry a message:
//
//     throw std::invalid_argument("not a number: " + text);
//     try { ... } catch (const std::invalid_argument& e) { use(e.what()); }
//
// Always catch by const reference.
//
// Grade: grade 08_error_handling/01_exceptions

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
