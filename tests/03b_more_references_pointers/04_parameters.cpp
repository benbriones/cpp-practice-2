#include "grader.hpp"
#include "03b_more_references_pointers/04_parameters.cpp"

namespace {

void add_one(int n) { n += 1; }
void add_ten(int *n) { *n += 10; }
void add_hundred(int &n) { n += 100; }
void misdirect(int *n) {
    int other = 0;
    n = &other;
    *n += 1000;
}

}  // namespace

TEST("trace_6: x after four calls") {
    int x = 0;
    add_one(x);
    add_ten(&x);
    add_hundred(x);
    misdirect(&x);
    CHECK_EQ(trace_6(), x);
}

TEST("parse_digit: digits") {
    int digit = -1;
    CHECK_EQ(parse_digit('7', digit), true);
    CHECK_EQ(digit, 7);
    CHECK_EQ(parse_digit('0', digit), true);
    CHECK_EQ(digit, 0);
    CHECK_EQ(parse_digit('9', digit), true);
    CHECK_EQ(digit, 9);
}

TEST("parse_digit: anything else leaves digit alone") {
    int digit = 123;
    CHECK_EQ(parse_digit('a', digit), false);
    CHECK_EQ(parse_digit(' ', digit), false);
    CHECK_EQ(parse_digit('/', digit), false);
    CHECK_EQ(parse_digit(':', digit), false);
    CHECK_EQ(digit, 123);
}

TEST("split_name: first and last") {
    std::string first = "old";
    std::string last = "old";
    split_name("Ada Lovelace", first, last);
    CHECK_EQ(first, "Ada");
    CHECK_EQ(last, "Lovelace");
}

TEST("split_name: splits at the first space only") {
    std::string first;
    std::string last;
    split_name("Grace Brewster Hopper", first, last);
    CHECK_EQ(first, "Grace");
    CHECK_EQ(last, "Brewster Hopper");
}

TEST("split_name: no space overwrites both") {
    std::string first = "old";
    std::string last = "old";
    split_name("Cher", first, last);
    CHECK_EQ(first, "Cher");
    CHECK_EQ(last, "");
    split_name("", first, last);
    CHECK_EQ(first, "");
    CHECK_EQ(last, "");
}

TEST("split_name: a space at either end") {
    std::string first;
    std::string last;
    split_name(" Ada", first, last);
    CHECK_EQ(first, "");
    CHECK_EQ(last, "Ada");
    split_name("Ada ", first, last);
    CHECK_EQ(first, "Ada");
    CHECK_EQ(last, "");
}

TEST("sum_with_extremes: all three results") {
    int lo = -999;
    int hi = -999;
    CHECK_EQ(sum_with_extremes({4, 9, 1, 7}, &lo, &hi), 21);
    CHECK_EQ(lo, 1);
    CHECK_EQ(hi, 9);
}

TEST("sum_with_extremes: negatives and a single element") {
    int lo = 0;
    int hi = 0;
    CHECK_EQ(sum_with_extremes({-3, -8, -1}, &lo, &hi), -12);
    CHECK_EQ(lo, -8);
    CHECK_EQ(hi, -1);
    CHECK_EQ(sum_with_extremes({5}, &lo, &hi), 5);
    CHECK_EQ(lo, 5);
    CHECK_EQ(hi, 5);
}

TEST("sum_with_extremes: skips nullptr out parameters") {
    int lo = -999;
    int hi = -999;
    CHECK_EQ(sum_with_extremes({4, 9, 1}, &lo, nullptr), 14);
    CHECK_EQ(lo, 1);
    CHECK_EQ(sum_with_extremes({4, 9, 1}, nullptr, &hi), 14);
    CHECK_EQ(hi, 9);
    CHECK_EQ(sum_with_extremes({4, 9, 1}, nullptr, nullptr), 14);
}

TEST("sum_with_extremes: empty writes nothing") {
    int lo = 123;
    int hi = 456;
    CHECK_EQ(sum_with_extremes({}, &lo, &hi), 0);
    CHECK_EQ(lo, 123);
    CHECK_EQ(hi, 456);
}

TEST("keep_larger: a nullptr best takes the candidate") {
    int x = -50;
    int *best = nullptr;
    keep_larger(best, &x);
    CHECK(best == &x, "best was nullptr, so it should now point at the candidate");
}

TEST("keep_larger: switches only to a larger value") {
    int x = 5;
    int y = 9;
    int z = 9;
    int *best = &x;
    keep_larger(best, &y);
    CHECK(best == &y, "9 > 5, so best should now point at y");
    keep_larger(best, &z);
    CHECK(best == &y, "9 is not larger than 9, so best should stay on y");
    keep_larger(best, &x);
    CHECK(best == &y, "5 is smaller, so best should stay on y");
}

TEST("keep_larger: finds the largest element in a loop") {
    std::vector<int> values{3, 8, 2, 8, 6};
    int *best = nullptr;
    for (int &value : values) {
        keep_larger(best, &value);
    }
    CHECK(best == &values[1], "best should end on the first 8 (values[1])");
    *best = 0;
    CHECK_EQ(values, {3, 0, 2, 8, 6});
}
