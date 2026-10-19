#include "grader.hpp"
#include "03_references_pointers/03_optional.cpp"

TEST("parse_int: plain numbers") {
    CHECK_EQ(parse_int("42"), 42);
    CHECK_EQ(parse_int("0"), 0);
    CHECK_EQ(parse_int("007"), 7);
}

TEST("parse_int: signs") {
    CHECK_EQ(parse_int("-17"), -17);
    CHECK_EQ(parse_int("+5"), 5);
}

TEST("parse_int: rejects empty input and lone signs") {
    CHECK_EQ(parse_int(""), std::nullopt);
    CHECK_EQ(parse_int("-"), std::nullopt);
    CHECK_EQ(parse_int("+"), std::nullopt);
}

TEST("parse_int: rejects anything that isn't digits") {
    CHECK_EQ(parse_int("12a"), std::nullopt);
    CHECK_EQ(parse_int("a12"), std::nullopt);
    CHECK_EQ(parse_int(" 12"), std::nullopt);
    CHECK_EQ(parse_int("1 2"), std::nullopt);
    CHECK_EQ(parse_int("3.5"), std::nullopt);
    CHECK_EQ(parse_int("--3"), std::nullopt);
}

TEST("parse_int: the limits of int") {
    CHECK_EQ(parse_int("2147483647"), 2147483647);
    CHECK_EQ(parse_int("-2147483648"), -2147483647 - 1);
}

TEST("parse_int: out of range") {
    CHECK_EQ(parse_int("2147483648"), std::nullopt);
    CHECK_EQ(parse_int("-2147483649"), std::nullopt);
    CHECK_EQ(parse_int("99999999999999999999999"), std::nullopt);
}

TEST("find_index: found") {
    const std::vector<std::string> items{"red", "green", "blue"};
    CHECK_EQ(find_index(items, "red"), 0);
    CHECK_EQ(find_index(items, "blue"), 2);
}

TEST("find_index: first occurrence") {
    CHECK_EQ(find_index({"a", "b", "a"}, "a"), 0);
}

TEST("find_index: missing") {
    CHECK_EQ(find_index({"red", "green"}, "purple"), std::nullopt);
    CHECK_EQ(find_index({}, "red"), std::nullopt);
}

TEST("first_negative") {
    CHECK_EQ(first_negative({3, -1, -5}), -1);
    CHECK_EQ(first_negative({-2147483647 - 1}), -2147483647 - 1);
}

TEST("first_negative: none") {
    CHECK_EQ(first_negative({0, 1, 2}), std::nullopt);
    CHECK_EQ(first_negative({}), std::nullopt);
}

TEST("average: has a value") {
    std::optional<double> result = average({1, 2});
    CHECK(result.has_value(), "average({1, 2}) returned std::nullopt");
    CHECK_NEAR(*result, 1.5);
    result = average({-4});
    CHECK(result.has_value(), "average({-4}) returned std::nullopt");
    CHECK_NEAR(*result, -4.0);
}

TEST("average: empty vector") {
    CHECK_EQ(average({}), std::nullopt);
}
