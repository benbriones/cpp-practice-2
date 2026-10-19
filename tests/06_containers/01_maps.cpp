#include "grader.hpp"
#include "06_containers/01_maps.cpp"

TEST("word_counts: counts repeated words") {
    CHECK_EQ(word_counts("one two two three three three"), {{"one", 1}, {"three", 3}, {"two", 2}});
}

TEST("word_counts: lower-cases and drops punctuation") {
    CHECK_EQ(word_counts("The cat, the HAT."), {{"cat", 1}, {"hat", 1}, {"the", 2}});
}

TEST("word_counts: digits and symbols separate words") {
    CHECK_EQ(word_counts("x1y--z  x"), {{"x", 2}, {"y", 1}, {"z", 1}});
}

TEST("word_counts: no words") {
    CHECK_EQ(word_counts(""), {});
    CHECK_EQ(word_counts(" 123 !? "), {});
}

TEST("most_common: highest count wins") {
    CHECK_EQ(most_common({{"apple", 2}, {"pear", 5}, {"plum", 1}}), "pear");
}

TEST("most_common: ties go to the alphabetically first word") {
    CHECK_EQ(most_common({{"zebra", 3}, {"apple", 3}, {"mango", 1}}), "apple");
}

TEST("most_common: empty map") {
    CHECK_EQ(most_common({}), "");
}

TEST("merge: adds counts for shared words") {
    CHECK_EQ(merge({{"a", 1}}, {{"a", 2}, {"b", 1}}), {{"a", 3}, {"b", 1}});
}

TEST("merge: with an empty map") {
    CHECK_EQ(merge({}, {{"x", 4}}), {{"x", 4}});
    CHECK_EQ(merge({{"x", 4}}, {}), {{"x", 4}});
}

TEST("merge: works with word_counts") {
    CHECK_EQ(merge(word_counts("a b"), word_counts("b c")), {{"a", 1}, {"b", 2}, {"c", 1}});
}

TEST("group_by_length: groups keep input order") {
    CHECK_EQ(group_by_length({"to", "be", "or", "not"}), {{2, {"to", "be", "or"}}, {3, {"not"}}});
}

TEST("group_by_length: keys are sorted") {
    CHECK_EQ(group_by_length({"elephant", "a", "cat", "I", "dog"}),
             {{1, {"a", "I"}}, {3, {"cat", "dog"}}, {8, {"elephant"}}});
}

TEST("group_by_length: empty input") {
    CHECK_EQ(group_by_length({}), {});
}
