#include "grader.hpp"
#include "09_streams_files/01_string_streams.cpp"

TEST("parse_ints: all integers") {
    CHECK_EQ(parse_ints("4 8 15 16 23 42"), {4, 8, 15, 16, 23, 42});
    CHECK_EQ(parse_ints("  -3\t7\n 0 "), {-3, 7, 0});
}

TEST("parse_ints: stops at the first non-integer") {
    CHECK_EQ(parse_ints("4 8 x 15"), {4, 8});
    CHECK_EQ(parse_ints("hello 1 2"), {});
}

TEST("parse_ints: empty or blank text") {
    CHECK_EQ(parse_ints(""), {});
    CHECK_EQ(parse_ints("   \n"), {});
}

TEST("read_valid_ints: skips bad tokens") {
    std::istringstream in("1 two 3 four 5");
    CHECK_EQ(read_valid_ints(in), {1, 3, 5});
}

TEST("read_valid_ints: several bad tokens in a row, across lines") {
    std::istringstream in("x y\nz 10\n\n-20 ? 30\n");
    CHECK_EQ(read_valid_ints(in), {10, -20, 30});
}

TEST("read_valid_ints: nothing valid or empty input") {
    std::istringstream junk("a b c");
    CHECK_EQ(read_valid_ints(junk), {});
    std::istringstream empty("");
    CHECK_EQ(read_valid_ints(empty), {});
}

TEST("format_row: column widths") {
    CHECK_EQ(format_row("Widget", 3, 4.5), "Widget          3      4.50");
    CHECK_EQ(format_row("Gizmo", 120, 1234.567), "Gizmo         120   1234.57");
}

TEST("format_row: long names aren't truncated") {
    CHECK_EQ(format_row("Extra-long name", 1, 0.5), "Extra-long name    1      0.50");
}

TEST("to_fixed: rounds to the requested decimals") {
    CHECK_EQ(to_fixed(3.14159, 2), "3.14");
    CHECK_EQ(to_fixed(2.0, 3), "2.000");
    CHECK_EQ(to_fixed(0.125, 1), "0.1");
}

TEST("to_fixed: zero decimals and negatives") {
    CHECK_EQ(to_fixed(2.7, 0), "3");
    CHECK_EQ(to_fixed(-0.5, 1), "-0.5");
    CHECK_EQ(to_fixed(-12.345, 1), "-12.3");
}
