#include "grader.hpp"
#include "03b_more_references_pointers/05_returning_references.cpp"

TEST("trace_7: v at the end") {
    std::vector<int> v{1, 2, 3};
    int &first = v[0];
    [[maybe_unused]] auto copy = v[1];
    auto &alias = v[2];
    first = 10;
    copy = 20;
    alias = 30;
    int &again = first;
    again += 5;
    CHECK_EQ(trace_7(), v);
}

TEST("clamp_all: changes the caller's vector") {
    std::vector<int> values{-5, 0, 5, 10, 15};
    clamp_all(values, 0, 10);
    CHECK_EQ(values, {0, 0, 5, 10, 10});
}

TEST("clamp_all: values already inside, and lo == hi") {
    std::vector<int> inside{1, 2, 3};
    clamp_all(inside, 0, 10);
    CHECK_EQ(inside, {1, 2, 3});
    std::vector<int> pinned{-1, 4, 9};
    clamp_all(pinned, 4, 4);
    CHECK_EQ(pinned, {4, 4, 4});
}

TEST("clamp_all: empty vector") {
    std::vector<int> values;
    clamp_all(values, 0, 1);
    CHECK_EQ(values, {});
}

TEST("max_ref: refers to the larger variable") {
    int x = 3;
    int y = 8;
    CHECK(&max_ref(x, y) == &y, "8 is larger, so max_ref should return a reference to y");
    CHECK(&max_ref(y, x) == &y, "8 is larger, so max_ref should return a reference to y");
}

TEST("max_ref: a on ties") {
    int x = 4;
    int y = 4;
    CHECK(&max_ref(x, y) == &x, "on a tie, max_ref should return a reference to a (x here)");
}

TEST("max_ref: assigning through the result") {
    int x = 3;
    int y = 8;
    max_ref(x, y) = 0;
    CHECK_EQ(x, 3);
    CHECK_EQ(y, 0);
    max_ref(x, y) += 10;
    CHECK_EQ(x, 13);
    CHECK_EQ(y, 0);
}

TEST("max_ref: vector elements") {
    std::vector<int> values{-7, -2};
    max_ref(values[0], values[1]) = 100;
    CHECK_EQ(values, {-7, 100});
}

TEST("longest: refers to the word inside the vector") {
    std::vector<std::string> words{"hi", "there", "you"};
    const std::string &word = longest(words);
    CHECK_EQ(word, "there");
    CHECK(&word == &words[1], "longest should return a reference to words[1], not to a copy");
}

TEST("longest: the first one on ties") {
    std::vector<std::string> words{"ab", "cde", "fgh"};
    CHECK(&longest(words) == &words[1], "\"cde\" and \"fgh\" tie, so it should be words[1]");
}

TEST("longest: one word, and empty words") {
    std::vector<std::string> one{"solo"};
    CHECK(&longest(one) == &one[0], "with one word, the result should be words[0]");
    std::vector<std::string> blanks{"", ""};
    CHECK(&longest(blanks) == &blanks[0], "every word has length 0, so it should be words[0]");
}

TEST("at_wrapped: ordinary indexes") {
    std::vector<int> values{10, 20, 30};
    CHECK(&at_wrapped(values, 0) == &values[0], "index 0 should refer to values[0] itself");
    CHECK(&at_wrapped(values, 2) == &values[2], "index 2 should refer to values[2] itself");
}

TEST("at_wrapped: negative indexes count from the end") {
    std::vector<int> values{10, 20, 30};
    CHECK_EQ(at_wrapped(values, -1), 30);
    CHECK_EQ(at_wrapped(values, -2), 20);
    CHECK_EQ(at_wrapped(values, -3), 10);
}

TEST("at_wrapped: wraps past either end") {
    std::vector<int> values{10, 20, 30};
    CHECK_EQ(at_wrapped(values, 3), 10);
    CHECK_EQ(at_wrapped(values, 7), 20);
    CHECK_EQ(at_wrapped(values, -4), 30);
    CHECK_EQ(at_wrapped(values, -9), 10);
    std::vector<int> one{5};
    CHECK_EQ(at_wrapped(one, 100), 5);
    CHECK_EQ(at_wrapped(one, -100), 5);
}

TEST("at_wrapped: assigning through the result") {
    std::vector<int> values{10, 20, 30};
    at_wrapped(values, -1) = 0;
    at_wrapped(values, 4) += 1;
    CHECK_EQ(values, {10, 21, 0});
}

TEST("count_for: adds a missing name with a count of 0") {
    std::vector<std::string> names;
    std::vector<int> counts;
    CHECK_EQ(count_for(names, counts, "ada"), 0);
    CHECK_EQ(names, {"ada"});
    CHECK_EQ(counts, {0});
}

TEST("count_for: refers to the count inside the vector") {
    std::vector<std::string> names{"ada", "bob"};
    std::vector<int> counts{3, 5};
    CHECK(&count_for(names, counts, "bob") == &counts[1],
          "count_for should return a reference to counts[1], not to a copy");
    CHECK_EQ(names, {"ada", "bob"});
}

TEST("count_for: counting with ++") {
    std::vector<std::string> names;
    std::vector<int> counts;
    ++count_for(names, counts, "ada");
    ++count_for(names, counts, "bob");
    ++count_for(names, counts, "ada");
    count_for(names, counts, "cy") += 10;
    CHECK_EQ(names, {"ada", "bob", "cy"});
    CHECK_EQ(counts, {2, 1, 10});
}
