#include "grader.hpp"
#include "03c_even_more_references_pointers/01_pass_by_value.cpp"

namespace {

int twice(int n) {
    n *= 2;
    return n;
}

void shout_all(std::vector<std::string> words) {
    for (std::string &w : words) w += "!";
}

std::vector<std::string> shouted(std::vector<std::string> words) {
    for (std::string &w : words) w += "!";
    return words;
}

}  // namespace

TEST("trace_1: a and b at the end") {
    int a = 5;
    int b = twice(a);
    twice(b);
    a = twice(a) + 1;
    CHECK_EQ(trace_1(), {a, b});
}

TEST("trace_2: words at the end") {
    std::vector<std::string> words{"hi", "yo"};
    shout_all(words);
    std::vector<std::string> louder = shouted(words);
    words[1] = louder[0];
    CHECK_EQ(trace_2(), words);
}

TEST("collatz_steps: 1 takes no steps") {
    CHECK_EQ(collatz_steps(1), 0);
}

TEST("collatz_steps: small starts") {
    CHECK_EQ(collatz_steps(2), 1);
    CHECK_EQ(collatz_steps(6), 8);
    CHECK_EQ(collatz_steps(7), 16);
}

TEST("collatz_steps: a long run") {
    CHECK_EQ(collatz_steps(27), 111);
}

TEST("collatz_steps: the caller's int is unchanged") {
    int start = 6;
    collatz_steps(start);
    CHECK_EQ(start, 6);
}

TEST("capitalize_words: every word") {
    CHECK_EQ(capitalize_words("hello big world"), "Hello Big World");
    CHECK_EQ(capitalize_words("x"), "X");
}

TEST("capitalize_words: leaves the rest of each word alone") {
    CHECK_EQ(capitalize_words("mIxEd case"), "MIxEd Case");
    CHECK_EQ(capitalize_words("Already Done"), "Already Done");
}

TEST("capitalize_words: extra spaces and non-letters") {
    CHECK_EQ(capitalize_words("  two  spaces "), "  Two  Spaces ");
    CHECK_EQ(capitalize_words("3 blind mice"), "3 Blind Mice");
    CHECK_EQ(capitalize_words(""), "");
    CHECK_EQ(capitalize_words("   "), "   ");
}

TEST("capitalize_words: the caller's string is unchanged") {
    std::string title = "dune messiah";
    std::string result = capitalize_words(title);
    CHECK_EQ(result, "Dune Messiah");
    CHECK_EQ(title, "dune messiah");
}

TEST("running_totals: sums so far") {
    CHECK_EQ(running_totals({1, 2, 3, 4}), {1, 3, 6, 10});
}

TEST("running_totals: negatives") {
    CHECK_EQ(running_totals({5, -5, 2}), {5, 0, 2});
    CHECK_EQ(running_totals({-1, -1, -1}), {-1, -2, -3});
}

TEST("running_totals: empty and one element") {
    CHECK_EQ(running_totals({}), {});
    CHECK_EQ(running_totals({7}), {7});
}

TEST("running_totals: the caller's vector is unchanged") {
    std::vector<int> values{1, 2, 3};
    std::vector<int> totals = running_totals(values);
    CHECK_EQ(totals, {1, 3, 6});
    CHECK_EQ(values, {1, 2, 3});
}
