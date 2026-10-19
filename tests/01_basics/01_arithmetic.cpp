#include "grader.hpp"
#include "01_basics/01_arithmetic.cpp"

TEST("average: whole-number result") {
    CHECK_NEAR(average(2, 4), 3.0);
}

TEST("average: keeps the fraction") {
    CHECK_NEAR(average(1, 2), 1.5);
    CHECK_NEAR(average(-3, 4), 0.5);
}

TEST("average: huge values don't overflow") {
    CHECK_NEAR(average(2'000'000'000, 2'000'000'000), 2'000'000'000.0);
}

TEST("celsius_to_fahrenheit: freezing and boiling") {
    CHECK_NEAR(celsius_to_fahrenheit(0), 32.0);
    CHECK_NEAR(celsius_to_fahrenheit(100), 212.0);
}

TEST("celsius_to_fahrenheit: fractional degrees") {
    CHECK_NEAR(celsius_to_fahrenheit(37.5), 99.5);
    CHECK_NEAR(celsius_to_fahrenheit(-40), -40.0);
}

TEST("last_digit: positive numbers") {
    CHECK_EQ(last_digit(1234), 4);
    CHECK_EQ(last_digit(7), 7);
    CHECK_EQ(last_digit(0), 0);
}

TEST("last_digit: negative numbers") {
    CHECK_EQ(last_digit(-57), 7);
    CHECK_EQ(last_digit(-10), 0);
}

TEST("seconds_in_years: small values") {
    CHECK_EQ(seconds_in_years(0), 0);
    CHECK_EQ(seconds_in_years(1), 31'536'000);
}

TEST("seconds_in_years: large values don't overflow") {
    CHECK_EQ(seconds_in_years(100), 3'153'600'000LL);
    CHECK_EQ(seconds_in_years(2'000), 63'072'000'000LL);
}
