#include "grader.hpp"
#include "13_operator_overloading/01_fraction.cpp"

// Reads the parts directly, so most tests don't depend on your operator<<.
std::string parts(const Fraction &f) {
    return std::to_string(f.numerator()) + "/" + std::to_string(f.denominator());
}

TEST("constructor: reduces to lowest terms") {
    CHECK_EQ(parts(Fraction(2, 4)), "1/2");
    CHECK_EQ(parts(Fraction(10, 5)), "2/1");
    CHECK_EQ(parts(Fraction(6, 9)), "2/3");
}

TEST("constructor: the sign lives in the numerator") {
    CHECK_EQ(parts(Fraction(1, -2)), "-1/2");
    CHECK_EQ(parts(Fraction(-3, -6)), "1/2");
    CHECK_EQ(parts(Fraction(-4, 6)), "-2/3");
}

TEST("constructor: whole numbers and zero") {
    CHECK_EQ(parts(Fraction(3)), "3/1");
    CHECK_EQ(parts(Fraction()), "0/1");
    CHECK_EQ(parts(Fraction(0, -5)), "0/1");
}

TEST("constructor: zero denominator throws") {
    CHECK_THROWS(std::invalid_argument, Fraction(1, 0));
}

TEST("operator+") {
    CHECK_EQ(parts(Fraction(1, 2) + Fraction(1, 3)), "5/6");
    CHECK_EQ(parts(Fraction(1, 2) + Fraction(1, 2)), "1/1");
    CHECK_EQ(parts(Fraction(1, 4) + Fraction(-3, 4)), "-1/2");
}

TEST("operator+: mixing with whole numbers, on either side") {
    CHECK_EQ(parts(Fraction(1, 2) + 1), "3/2");
    CHECK_EQ(parts(2 + Fraction(1, 3)), "7/3");
}

TEST("operator- and unary minus") {
    CHECK_EQ(parts(Fraction(3, 4) - Fraction(1, 4)), "1/2");
    CHECK_EQ(parts(Fraction(1, 4) - Fraction(3, 4)), "-1/2");
    CHECK_EQ(parts(-Fraction(2, 3)), "-2/3");
    CHECK_EQ(parts(-Fraction(-2, 3)), "2/3");
}

TEST("operator* and operator/") {
    CHECK_EQ(parts(Fraction(2, 3) * Fraction(3, 4)), "1/2");
    CHECK_EQ(parts(Fraction(1, 2) / Fraction(1, 4)), "2/1");
    CHECK_EQ(parts(Fraction(1, 2) / Fraction(-1, 4)), "-2/1");
    CHECK_EQ(parts(Fraction(-1, 2) * -2), "1/1");
}

TEST("operator/: dividing by zero throws") {
    CHECK_THROWS(std::invalid_argument, Fraction(1, 2) / Fraction(0));
}

TEST("operator==") {
    CHECK(Fraction(1, 2) == Fraction(2, 4), "1/2 should equal 2/4");
    CHECK(Fraction(4, 2) == 2, "4/2 should equal 2");
    CHECK(!(Fraction(1, 2) == Fraction(1, 3)), "1/2 should not equal 1/3");
    CHECK(Fraction(1, 2) != Fraction(-1, 2), "1/2 should not equal -1/2");
}

TEST("operator<=>: ordering") {
    CHECK(Fraction(1, 3) < Fraction(1, 2), "1/3 < 1/2");
    CHECK(Fraction(-1, 2) < Fraction(1, 3), "-1/2 < 1/3");
    CHECK(Fraction(-1, 2) < Fraction(-1, 3), "-1/2 < -1/3");
    CHECK(Fraction(2, 4) <= Fraction(1, 2), "2/4 <= 1/2");
    CHECK(Fraction(3, 2) > 1, "3/2 > 1");
    CHECK(!(Fraction(2, 3) > Fraction(3, 4)), "2/3 is not > 3/4");
}

TEST("operator<<") {
    std::ostringstream out;
    out << Fraction(3, 4) << " " << Fraction(4, 2) << " " << Fraction(1, -2) << " " << Fraction(0);
    CHECK_EQ(out.str(), "3/4 2 -1/2 0");
}

TEST("operator double is explicit") {
    CHECK_NEAR(static_cast<double>(Fraction(1, 4)), 0.25);
    CHECK_NEAR(static_cast<double>(Fraction(-7, 2)), -3.5);
    CHECK(!std::is_convertible_v<Fraction, double>, "operator double() should be explicit");
}
