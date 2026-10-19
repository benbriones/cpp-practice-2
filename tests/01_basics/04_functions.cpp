#include "grader.hpp"
#include "01_basics/04_functions.cpp"

TEST("max_of: two ints") {
    CHECK_EQ(max_of(3, 7), 7);
    CHECK_EQ(max_of(7, 3), 7);
    CHECK_EQ(max_of(-2, -5), -2);
}

TEST("max_of: three ints") {
    CHECK_EQ(max_of(1, 2, 3), 3);
    CHECK_EQ(max_of(3, 2, 1), 3);
    CHECK_EQ(max_of(2, 9, 4), 9);
}

TEST("max_of: two doubles") {
    CHECK_NEAR(max_of(2.5, 2.25), 2.5);
    CHECK_NEAR(max_of(-0.5, -1.5), -0.5);
}

TEST("repeat: default arguments") {
    CHECK_EQ(repeat("ab"), "abab");
    CHECK_EQ(repeat("x", 4), "xxxx");
}

TEST("repeat: with a separator") {
    CHECK_EQ(repeat("ab", 3, "-"), "ab-ab-ab");
    CHECK_EQ(repeat("hi", 1, ", "), "hi");
}

TEST("repeat: zero or negative times") {
    CHECK_EQ(repeat("ab", 0), "");
    CHECK_EQ(repeat("ab", -3, "-"), "");
}

TEST("power: small exponents") {
    CHECK_EQ(power(2, 0), 1);
    CHECK_EQ(power(2, 10), 1024);
    CHECK_EQ(power(-3, 3), -27);
    CHECK_EQ(power(5, 1), 5);
}

TEST("power: large results") {
    CHECK_EQ(power(2, 62), 4'611'686'018'427'387'904LL);
    CHECK_EQ(power(10, 18), 1'000'000'000'000'000'000LL);
}

TEST("to_binary") {
    CHECK_EQ(to_binary(0), "0");
    CHECK_EQ(to_binary(1), "1");
    CHECK_EQ(to_binary(6), "110");
    CHECK_EQ(to_binary(255), "11111111");
    CHECK_EQ(to_binary(1024), "10000000000");
}

TEST("next_ticket: counts up across calls") {
    CHECK_EQ(next_ticket(), 1);
    CHECK_EQ(next_ticket(), 2);
    CHECK_EQ(next_ticket(), 3);
}
