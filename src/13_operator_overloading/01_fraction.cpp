// === Lesson: Overloading operators ===========================================
//
// An operator is a function with a special name: `a + b` calls operator+(a, b),
// and `out << x` calls operator<<(out, x). Write those functions for your own
// type and its values work with the usual symbols:
//
//     struct Money {
//         long long cents = 0;
//         Money(long long c = 0) : cents(c) {}   // not explicit: 5 converts to Money
//     };
//
//     Money operator+(const Money& a, const Money& b) {
//         return Money(a.cents + b.cents);
//     }
//
//     Money m(250);
//     m + 5;   // operator+(m, Money(5))
//     5 + m;   // works too: a free function converts either side
//
// Member or free function? A member operator needs its left operand to already be
// the class type, so with a member `Money operator+(const Money&) const`, 5 + m
// wouldn't compile. Symmetric operators (+ - * / == <=>) are usually free.
// Arithmetic operators return a new value and leave their operands alone.
//
// Comparisons in C++20: define == and the compiler derives != from it. Define <=>
// (the "spaceship") and it derives < <= > >= from it. Built-in types already
// have <=>, which returns an ordering (less, equal or greater):
//
//     std::strong_ordering operator<=>(const Money& a, const Money& b) {
//         return a.cents <=> b.cents;
//     }
//
// A hand-written <=> doesn't give you ==, so write both.
//
// Printing: operator<< takes the stream by reference and returns it, so that
// out << a << b runs as operator<<(operator<<(out, a), b):
//
//     std::ostream& operator<<(std::ostream& out, const Money& m) {
//         return out << m.cents << "c";
//     }
//
// A conversion operator turns your type into another. Mark it explicit so it only
// runs when asked: `explicit operator double() const` allows
// static_cast<double>(m) but not `double d = m;`. An implicit one would also make
// m + 5 ambiguous: convert 5 to Money, or m to double?
//
// <numeric> has std::gcd, the greatest common divisor; it ignores signs, so
// std::gcd(-4, 6) == 2.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-operator-overloading
//            https://www.learncpp.com/cpp-tutorial/overloading-the-comparison-operators
//
// === Exercise: Fraction ======================================================
// A Fraction that always stays in lowest terms, with the sign on the numerator:
// Fraction(2, -4) stores -1/2, and Fraction(0, 5) stores 0/1. A zero
// denominator throws std::invalid_argument.
//
// ./grade 13_operator_overloading/01_fraction

#include <compare>
#include <numeric>
#include <ostream>
#include <stdexcept>

class Fraction {
public:
    // Build the fraction numerator/denominator, stored in lowest terms.
    // Keep the sign on the numerator, so the stored denominator is always positive.
    // Zero is stored as 0/1. A zero denominator throws std::invalid_argument.
    //
    // Example:
    //   Fraction(2, 4) stores 1/2, Fraction(-3, -6) stores 1/2
    //   Fraction(2, -4) stores -1/2, Fraction(0, -5) stores 0/1
    //   Fraction(3) stores 3/1, Fraction() stores 0/1
    //
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

    // Unary minus: return this fraction with its sign flipped.
    // The fraction itself doesn't change.
    //
    // Example:
    //   -Fraction(2, 3) is -2/3, -Fraction(-2, 3) is 2/3
    Fraction operator-() const {
        throw "TODO";
    }

    // Convert to double, only when asked for: static_cast<double>(f).
    // Being explicit, it never runs implicitly, as in `double d = f;`.
    //
    // Example:
    //   static_cast<double>(Fraction(1, 4)) is 0.25
    //   static_cast<double>(Fraction(-7, 2)) is -3.5
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

// Return a divided by b, in lowest terms.
// Dividing by a zero fraction throws std::invalid_argument.
//
// Example:
//   Fraction(1, 2) / Fraction(1, 4) is 2/1
//   Fraction(1, 2) / Fraction(-1, 4) is -2/1
//   Fraction(1, 2) / Fraction(0) throws std::invalid_argument
Fraction operator/(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

bool operator==(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

// Return whether a is less than, equal to or greater than b.
// Compare a/b with c/d by comparing a*d with c*b (denominators are positive).
// Integers already support <=>: (x <=> y) is a std::strong_ordering.
//
// Example:
//   Fraction(1, 3) < Fraction(1, 2)      // 1*2 = 2 is less than 1*3 = 3
//   Fraction(-1, 2) < Fraction(-1, 3)    // -1*3 = -3 is less than -1*2 = -2
//   Fraction(2, 4) <= Fraction(1, 2)     // equal: both are 1/2
//
// The compiler derives < <= > >= from this one function.
std::strong_ordering operator<=>(const Fraction& a, const Fraction& b) {
    throw "TODO";
}

// Print f as "numerator/denominator", like "3/4" or "-1/2".
// Print just the numerator, like "2", when the denominator is 1.
// Return the stream so calls chain: out << a << " " << b.
//
// Example:
//   out << Fraction(3, 4) << " " << Fraction(4, 2);    // prints "3/4 2"
//   out << Fraction(1, -2) << " " << Fraction(0);      // prints "-1/2 0"
std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    throw "TODO";
}
