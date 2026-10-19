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
