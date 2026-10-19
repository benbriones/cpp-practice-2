#include "grader.hpp"
#include "02_strings_vectors/03_split_and_join.cpp"

TEST("split: simple fields") {
    CHECK_EQ(split("a,b,c", ','), {"a", "b", "c"});
    CHECK_EQ(split("one two", ' '), {"one", "two"});
}

TEST("split: no delimiter present") {
    CHECK_EQ(split("abc", ','), {"abc"});
}

TEST("split: keeps empty fields") {
    CHECK_EQ(split("a,b,,c", ','), {"a", "b", "", "c"});
    CHECK_EQ(split(",a,", ','), {"", "a", ""});
    CHECK_EQ(split(",", ','), {"", ""});
}

TEST("split: empty string") {
    CHECK_EQ(split("", ','), {});
}

TEST("join") {
    CHECK_EQ(join({"a", "b", "c"}, ", "), "a, b, c");
    CHECK_EQ(join({"2024", "01", "31"}, "-"), "2024-01-31");
}

TEST("join: zero or one part") {
    CHECK_EQ(join({}, ", "), "");
    CHECK_EQ(join({"solo"}, ", "), "solo");
}

TEST("split then join round-trips") {
    CHECK_EQ(join(split("x;y;;z", ';'), ";"), "x;y;;z");
}

TEST("trim: both ends") {
    CHECK_EQ(trim("  hello  "), "hello");
    CHECK_EQ(trim("\t\n hi there \n"), "hi there");
}

TEST("trim: nothing to trim") {
    CHECK_EQ(trim("hello"), "hello");
    CHECK_EQ(trim("a b"), "a b");
}

TEST("trim: only whitespace or empty") {
    CHECK_EQ(trim("   \t\n"), "");
    CHECK_EQ(trim(""), "");
}

TEST("to_upper") {
    CHECK_EQ(to_upper("hello"), "HELLO");
    CHECK_EQ(to_upper("Mixed Case 123!"), "MIXED CASE 123!");
    CHECK_EQ(to_upper(""), "");
}

TEST("to_upper: caller's string is unchanged") {
    std::string original = "keep me";
    std::string upper = to_upper(original);
    CHECK_EQ(original, "keep me");
    CHECK_EQ(upper, "KEEP ME");
}
