#include "grader.hpp"
#include "03b_more_references_pointers/03_nullptr.cpp"

TEST("trace_5: which conditions are true") {
    // (1) p points somewhere  (4) q is null  (5) s points at a 1
    CHECK_EQ(trace_5(), {1, 4, 5});
}

TEST("value_or: follows a real pointer") {
    int x = 42;
    CHECK_EQ(value_or(&x, -1), 42);
}

TEST("value_or: fallback for nullptr") {
    CHECK_EQ(value_or(nullptr, -1), -1);
    CHECK_EQ(value_or(nullptr, 7), 7);
}

TEST("value_or: a pointer to 0 is not null") {
    int zero = 0;
    CHECK(value_or(&zero, -1) == 0, "p points at a 0, which is a real value: test p, not *p");
}

TEST("find_first_even: points at the element itself") {
    std::vector<int> values{7, 3, 8, 5, 4};
    const int *found = find_first_even(values);
    CHECK(found != nullptr, "find_first_even returned nullptr, but 8 is even");
    CHECK(found == &values[2], "should point at values[2] itself, not at a copy");
}

TEST("find_first_even: negatives and zero") {
    std::vector<int> negatives{-3, -4};
    CHECK(find_first_even(negatives) == &negatives[1], "-4 is even and -3 isn't (-3 % 2 is -1)");
    std::vector<int> zero{1, 0};
    CHECK(find_first_even(zero) == &zero[1], "0 is even");
}

TEST("find_first_even: nullptr when there is none") {
    std::vector<int> odds{1, 3, 5};
    CHECK_EQ(find_first_even(odds), nullptr);
    std::vector<int> empty;
    CHECK_EQ(find_first_even(empty), nullptr);
}

TEST("find_last: the last match") {
    std::vector<int> values{5, 1, 5, 2};
    CHECK(find_last(values, 5) == &values[2], "should point at the LAST 5 (values[2])");
    CHECK(find_last(values, 2) == &values[3], "should point at values[3]");
}

TEST("find_last: writing through the result") {
    std::vector<int> values{5, 1, 5, 2};
    *find_last(values, 5) = 0;
    CHECK_EQ(values, {5, 1, 0, 2});
}

TEST("find_last: nullptr when missing") {
    std::vector<int> values{1, 2, 3};
    CHECK_EQ(find_last(values, 9), nullptr);
    std::vector<int> empty;
    CHECK_EQ(find_last(empty, 1), nullptr);
}

TEST("find_name: points at the matching string") {
    std::vector<std::string> names{"Ada", "Bob", "Cy"};
    std::string *found = find_name(names, "Bob");
    CHECK(found != nullptr, "find_name returned nullptr, but \"Bob\" is in the list");
    CHECK(found == &names[1], "should point at names[1] itself, not at a copy");
}

TEST("find_name: renaming through the result") {
    std::vector<std::string> names{"Ada", "Bob", "Cy"};
    *find_name(names, "Bob") = "Robert";
    CHECK_EQ(names, {"Ada", "Robert", "Cy"});
}

TEST("find_name: the first match, and exact matches only") {
    std::vector<std::string> names{"Ada", "ada", "Ada"};
    CHECK(find_name(names, "Ada") == &names[0], "should point at the FIRST \"Ada\"");
    CHECK(find_name(names, "ada") == &names[1], "the match is case-sensitive");
    CHECK_EQ(find_name(names, "Ad"), nullptr);
}

TEST("find_name: nullptr when missing") {
    std::vector<std::string> names{"Ada"};
    CHECK_EQ(find_name(names, "Bob"), nullptr);
    std::vector<std::string> empty;
    CHECK_EQ(find_name(empty, "Ada"), nullptr);
}

TEST("max_of: points at the larger") {
    int x = 3;
    int y = 8;
    CHECK(max_of(&x, &y) == &y, "8 is larger, so the result should be &y");
    CHECK(max_of(&y, &x) == &y, "8 is larger, so the result should be &y");
}

TEST("max_of: a on ties") {
    int x = -2;
    int y = -2;
    CHECK(max_of(&x, &y) == &x, "on a tie, the result should be a (&x here)");
}

TEST("max_of: one nullptr") {
    int x = -100;
    CHECK(max_of(&x, nullptr) == &x, "b is nullptr, so the result should be a");
    CHECK(max_of(nullptr, &x) == &x, "a is nullptr, so the result should be b");
}

TEST("max_of: both nullptr") {
    CHECK_EQ(max_of(nullptr, nullptr), nullptr);
}
