#include "grader.hpp"
#include "08_error_handling/03_error_strategies.cpp"

TEST("try_parse_age: valid ages") {
    int age = -1;
    CHECK_EQ(try_parse_age("42", age), true);
    CHECK_EQ(age, 42);
    CHECK_EQ(try_parse_age("0", age), true);
    CHECK_EQ(age, 0);
    CHECK_EQ(try_parse_age("150", age), true);
    CHECK_EQ(age, 150);
    CHECK_EQ(try_parse_age("007", age), true);
    CHECK_EQ(age, 7);
}

TEST("try_parse_age: invalid text returns false") {
    int age = -1;
    CHECK_EQ(try_parse_age("", age), false);
    CHECK_EQ(try_parse_age("abc", age), false);
    CHECK_EQ(try_parse_age("4 2", age), false);
    CHECK_EQ(try_parse_age(" 42", age), false);
    CHECK_EQ(try_parse_age("-1", age), false);
    CHECK_EQ(try_parse_age("+5", age), false);
}

TEST("try_parse_age: out-of-range values return false") {
    int age = -1;
    CHECK_EQ(try_parse_age("151", age), false);
    CHECK_EQ(try_parse_age("999", age), false);
    CHECK_EQ(try_parse_age("1000", age), false);
    CHECK_EQ(try_parse_age("99999999999999", age), false);
}

TEST("try_parse_age: failure leaves out unchanged") {
    int age = 33;
    try_parse_age("nope", age);
    CHECK_EQ(age, 33);
    try_parse_age("200", age);
    CHECK_EQ(age, 33);
}

TEST("parse_age") {
    CHECK_EQ(parse_age("42"), 42);
    CHECK_EQ(parse_age("0"), 0);
    CHECK_EQ(parse_age("151"), std::nullopt);
    CHECK_EQ(parse_age("x"), std::nullopt);
    CHECK_EQ(parse_age(""), std::nullopt);
}

TEST("parse_age_or_throw: valid") {
    CHECK_EQ(parse_age_or_throw("42"), 42);
    CHECK_EQ(parse_age_or_throw("150"), 150);
}

TEST("parse_age_or_throw: invalid throws with a message") {
    CHECK_THROWS(std::invalid_argument, parse_age_or_throw("old"));
    CHECK_THROWS(std::invalid_argument, parse_age_or_throw("151"));
    std::string what_for_12x = "(nothing thrown)";
    try {
        parse_age_or_throw("12x");
    } catch (const std::invalid_argument &e) {
        what_for_12x = e.what();
    }
    CHECK_EQ(what_for_12x, "invalid age: 12x");
}

TEST("average_age: skips invalid entries") {
    CHECK_EQ(average_age({"20", "30"}), 25.0);
    CHECK_EQ(average_age({"20", "abc", "31", "500"}), 25.5);
}

TEST("average_age: nothing valid") {
    CHECK_EQ(average_age({"x", "-1"}), std::nullopt);
    CHECK_EQ(average_age({}), std::nullopt);
}
