#include "grader.hpp"
#include "08_error_handling/01_exceptions.cpp"

TEST("parse_positive: valid numbers") {
    CHECK_EQ(parse_positive("42"), 42);
    CHECK_EQ(parse_positive("1"), 1);
    CHECK_EQ(parse_positive("007"), 7);
    CHECK_EQ(parse_positive("2147483647"), 2'147'483'647);
}

TEST("parse_positive: not a number throws invalid_argument") {
    CHECK_THROWS(std::invalid_argument, parse_positive("abc"));
    CHECK_THROWS(std::invalid_argument, parse_positive(""));
    CHECK_THROWS(std::invalid_argument, parse_positive("12abc"));
    CHECK_THROWS(std::invalid_argument, parse_positive(" 12"));
    CHECK_THROWS(std::invalid_argument, parse_positive("-5"));
    CHECK_THROWS(std::invalid_argument, parse_positive("3.5"));
}

TEST("parse_positive: zero throws out_of_range") {
    CHECK_THROWS(std::out_of_range, parse_positive("0"));
    CHECK_THROWS(std::out_of_range, parse_positive("000"));
}

TEST("parse_positive: too big throws out_of_range") {
    CHECK_THROWS(std::out_of_range, parse_positive("2147483648"));
    CHECK_THROWS(std::out_of_range, parse_positive("99999999999999999999"));
}

TEST("checked_at: valid indexes") {
    const std::vector<int> values{10, 20, 30};
    CHECK_EQ(checked_at(values, 0), 10);
    CHECK_EQ(checked_at(values, 2), 30);
}

TEST("checked_at: bad indexes throw out_of_range") {
    const std::vector<int> values{10, 20, 30};
    CHECK_THROWS(std::out_of_range, checked_at(values, 3));
    CHECK_THROWS(std::out_of_range, checked_at(values, -1));
    CHECK_THROWS(std::out_of_range, checked_at({}, 0));
}

TEST("checked_at: the message") {
    const std::vector<int> values{10, 20, 30};
    std::string what_for_index_5 = "(nothing thrown)";
    try {
        checked_at(values, 5);
    } catch (const std::out_of_range& e) {
        what_for_index_5 = e.what();
    }
    CHECK_EQ(what_for_index_5, "index 5 out of range for size 3");
    std::string what_for_index_minus_1 = "(nothing thrown)";
    try {
        checked_at(values, -1);
    } catch (const std::out_of_range& e) {
        what_for_index_minus_1 = e.what();
    }
    CHECK_EQ(what_for_index_minus_1, "index -1 out of range for size 3");
}

TEST("safe_divide") {
    CHECK_NEAR(safe_divide(7, 2), 3.5);
    CHECK_NEAR(safe_divide(-1, 4), -0.25);
}

TEST("safe_divide: by zero") {
    CHECK_THROWS(std::domain_error, safe_divide(1, 0));
    std::string what_for_divide_by_zero = "(nothing thrown)";
    try {
        safe_divide(1, 0);
    } catch (const std::domain_error& e) {
        what_for_divide_by_zero = e.what();
    }
    CHECK_EQ(what_for_divide_by_zero, "division by zero");
}

TEST("sum_valid: skips texts that throw") {
    CHECK_EQ(sum_valid({"10", "abc", "0", "5", "99999999999", "-3", "20"}), 35);
    CHECK_EQ(sum_valid({"x", "y"}), 0);
    CHECK_EQ(sum_valid({}), 0);
}

TEST("try_parse: reports each outcome") {
    CHECK_EQ(try_parse("42"), "ok: 42");
    CHECK_EQ(try_parse("4x2"), "invalid argument");
    CHECK_EQ(try_parse(""), "invalid argument");
    CHECK_EQ(try_parse("0"), "out of range");
    CHECK_EQ(try_parse("5000000000"), "out of range");
}
