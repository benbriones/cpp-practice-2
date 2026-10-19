#include "grader.hpp"
#include "03_references_pointers/05_lifetime_bugs.cpp"

TEST("append_doubles: appends a doubled copy of each element") {
    std::vector<int> values{1, 2, 3};
    append_doubles(values);
    CHECK_EQ(values, {1, 2, 3, 2, 4, 6});
}

TEST("append_doubles: a single element") {
    std::vector<int> values{5};
    append_doubles(values);
    CHECK_EQ(values, {5, 10});
}

TEST("append_doubles: empty vector") {
    std::vector<int> values;
    append_doubles(values);
    CHECK_EQ(values, {});
}

TEST("make_greeting") {
    CHECK_EQ(std::string(make_greeting("Ada")), "Hello, Ada! Welcome to the course.");
    CHECK_EQ(std::string(make_greeting("Bjarne")), "Hello, Bjarne! Welcome to the course.");
}

TEST("first_or_default: non-empty list") {
    const std::vector<std::string> names{"Grace", "Alan"};
    const std::string& first = first_or_default(names);
    CHECK_EQ(first, "Grace");
}

TEST("first_or_default: empty list") {
    const std::vector<std::string> names;
    const std::string& first = first_or_default(names);
    CHECK_EQ(first, "anonymous user (no name given)");
}

TEST("first_or_default: the result can be copied") {
    const std::vector<std::string> names;
    std::string copy = first_or_default(names);
    CHECK_EQ(copy, "anonymous user (no name given)");
}

TEST("shout_all: short words") {
    auto shouted = shout_all({"hi", "there"});
    std::vector<std::string> copies(shouted.begin(), shouted.end());
    CHECK_EQ(copies, {"HI", "THERE"});
}

TEST("shout_all: long words") {
    auto shouted = shout_all({"antidisestablishmentarianism", "supercalifragilistic"});
    std::vector<std::string> copies(shouted.begin(), shouted.end());
    CHECK_EQ(copies, {"ANTIDISESTABLISHMENTARIANISM", "SUPERCALIFRAGILISTIC"});
}

TEST("shout_all: empty list") {
    auto shouted = shout_all({});
    CHECK(shouted.empty(), "shout_all({}) should return an empty vector");
}
