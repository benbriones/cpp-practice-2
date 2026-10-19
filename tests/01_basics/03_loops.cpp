#include "grader.hpp"
#include "01_basics/03_loops.cpp"

TEST("sum_of_digits: positive numbers") {
    CHECK_EQ(sum_of_digits(123), 6);
    CHECK_EQ(sum_of_digits(9), 9);
    CHECK_EQ(sum_of_digits(1000), 1);
    CHECK_EQ(sum_of_digits(987654321), 45);
}

TEST("sum_of_digits: zero and negatives") {
    CHECK_EQ(sum_of_digits(0), 0);
    CHECK_EQ(sum_of_digits(-123), 6);
}

TEST("is_prime: small numbers") {
    CHECK_EQ(is_prime(2), true);
    CHECK_EQ(is_prime(3), true);
    CHECK_EQ(is_prime(4), false);
    CHECK_EQ(is_prime(9), false);
    CHECK_EQ(is_prime(17), true);
}

TEST("is_prime: numbers below 2") {
    CHECK_EQ(is_prime(1), false);
    CHECK_EQ(is_prime(0), false);
    CHECK_EQ(is_prime(-7), false);
}

TEST("is_prime: large numbers, quickly") {
    CHECK_EQ(is_prime(2'147'483'647), true);
    CHECK_EQ(is_prime(2'147'483'641), false);
    int primes_from_1e9_to_1e9_plus_200 = 0;
    for (int n = 1'000'000'000; n < 1'000'000'200; ++n) {
        if (is_prime(n)) ++primes_from_1e9_to_1e9_plus_200;
    }
    CHECK_EQ(primes_from_1e9_to_1e9_plus_200, 10);
}

TEST("gcd: common cases") {
    CHECK_EQ(gcd(12, 18), 6);
    CHECK_EQ(gcd(18, 12), 6);
    CHECK_EQ(gcd(17, 5), 1);
    CHECK_EQ(gcd(100, 75), 25);
}

TEST("gcd: zero and equal inputs") {
    CHECK_EQ(gcd(0, 9), 9);
    CHECK_EQ(gcd(9, 0), 9);
    CHECK_EQ(gcd(7, 7), 7);
}

TEST("collatz_steps: known values") {
    CHECK_EQ(collatz_steps(1), 0);
    CHECK_EQ(collatz_steps(2), 1);
    CHECK_EQ(collatz_steps(6), 8);
    CHECK_EQ(collatz_steps(27), 111);
}
