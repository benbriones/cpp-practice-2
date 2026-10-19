// Exercise: Fraction
// A Fraction that always stays in lowest terms, with the sign on the numerator:
// Fraction(2, -4) stores -1/2, and Fraction(0, 5) stores 0/1. A zero
// denominator throws std::invalid_argument.
//
// An operator is a function with a special name: `a + b` calls operator+(a, b).
// Free (non-member) operators let conversions apply to both sides, so 1 + f
// works as well as f + 1. In C++20, one operator<=> gives you < <= > >= too.
//
// Grade: grade 13_operator_overloading/01_fraction

#include <compare>
#include <numeric>
#include <ostream>
#include <stdexcept>

class Fraction {
public:
    // Not explicit on purpose: a whole number converts to n/1, so f + 1 works.
    Fraction(long long numerator = 0, long long denominator = 1) {
        throw "TODO";
    }

    long long numerator() const {
        throw "TODO";
    }

    long long denominator() const {
        throw "TODO";
    }

    // Unary minus: -Fraction(2, 3) is -2/3.
    Fraction operator-() const {
        throw "TODO";
    }

    // Conversion to double, only when asked for: static_cast<double>(f).
    explicit operator double() const {
        throw "TODO";
    }

private:
    // TODO: data members
};

Fraction operator+(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

Fraction operator-(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

Fraction operator*(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

// Dividing by a zero fraction throws std::invalid_argument.
Fraction operator/(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

bool operator==(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

// Compare a/b with c/d by comparing a*d with c*b (denominators are positive).
// Integers already support <=>: (x <=> y) is a std::strong_ordering.
std::strong_ordering operator<=>(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

// Prints "3/4", "-1/2", or just "2" when the denominator is 1.
// Return the stream so calls chain: out << a << " " << b.
std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    throw "TODO";
}
