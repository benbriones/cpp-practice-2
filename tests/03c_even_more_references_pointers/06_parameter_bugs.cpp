#include "grader.hpp"
#include "03c_even_more_references_pointers/06_parameter_bugs.cpp"

TEST("add_tag: appends a new tag") {
    std::vector<std::string> tags{"red"};
    add_tag(tags, "blue");
    CHECK_EQ(tags, {"red", "blue"});
}

TEST("add_tag: skips a tag it already has") {
    std::vector<std::string> tags{"red", "blue"};
    add_tag(tags, "red");
    add_tag(tags, "green");
    add_tag(tags, "green");
    CHECK_EQ(tags, {"red", "blue", "green"});
}

TEST("split_time: minutes and seconds") {
    int m = -1;
    int s = -1;
    split_time(135, m, s);
    CHECK_EQ(m, 2);
    CHECK_EQ(s, 15);
}

TEST("split_time: under a minute, and exact minutes") {
    int m = -1;
    int s = -1;
    split_time(59, m, s);
    CHECK_EQ(m, 0);
    CHECK_EQ(s, 59);
    split_time(120, m, s);
    CHECK_EQ(m, 2);
    CHECK_EQ(s, 0);
}

TEST("underscored: replaces spaces") {
    CHECK_EQ(underscored("my file name"), "my_file_name");
    CHECK_EQ(underscored("none"), "none");
    CHECK_EQ(underscored(""), "");
}

TEST("underscored: the caller's string is unchanged") {
    std::string name = "my file";
    std::string safe = underscored(name);
    CHECK_EQ(safe, "my_file");
    CHECK_EQ(name, "my file");
}

TEST("replace_zeros: changes the caller's vector") {
    std::vector<int> values{0, 3, 0};
    replace_zeros(values, 9);
    CHECK_EQ(values, {9, 3, 9});
}

TEST("replace_zeros: no zeros, and empty") {
    std::vector<int> values{1, -2};
    replace_zeros(values, 9);
    CHECK_EQ(values, {1, -2});
    std::vector<int> empty;
    replace_zeros(empty, 9);
    CHECK(empty.empty());
}

TEST("select_first: points at the first match") {
    std::vector<int> values{4, 5, 5};
    int *selected = nullptr;
    select_first(values, 5, selected);
    CHECK(selected == &values[1], "selected should now point at values[1], the first 5");
}

TEST("select_first: nullptr when nothing matches") {
    std::vector<int> values{4, 5};
    int *selected = &values[0];
    select_first(values, 9, selected);
    CHECK(selected == nullptr, "no element is 9, so selected should be nullptr");
}

TEST("select_first: writing through the result") {
    std::vector<int> values{4, 5, 6};
    int *selected = nullptr;
    select_first(values, 6, selected);
    CHECK(selected != nullptr, "select_first left selected as nullptr, but values holds a 6");
    *selected = 0;
    CHECK_EQ(values, {4, 5, 0});
}

TEST("clear_matches: clears the matching slots") {
    int a = 1;
    int b = 2;
    std::vector<int *> slots{&a, &b, nullptr, &a};
    clear_matches(slots, 1);
    CHECK(slots[0] == nullptr, "slots[0] points at a 1, so it should now be nullptr");
    CHECK(slots[1] == &b, "slots[1] points at a 2, so it should still point at b");
    CHECK(slots[2] == nullptr, "slots[2] was nullptr and should stay that way");
    CHECK(slots[3] == nullptr, "slots[3] points at a 1, so it should now be nullptr");
    CHECK_EQ(a, 1);
}

TEST("clear_matches: no matches changes nothing") {
    int a = 1;
    std::vector<int *> slots{&a, nullptr};
    clear_matches(slots, 5);
    CHECK(slots[0] == &a, "a is 1, not 5, so slots[0] should still point at a");
    CHECK(slots[1] == nullptr, "slots[1] was nullptr and should stay that way");
}

TEST("subtract_from_all: a plain amount") {
    std::vector<int> values{5, 7, 9};
    subtract_from_all(values, 2);
    CHECK_EQ(values, {3, 5, 7});
}

TEST("subtract_from_all: one of its own elements") {
    std::vector<int> values{5, 7, 9};
    subtract_from_all(values, values[0]);
    CHECK_EQ(values, {0, 2, 4});
    std::vector<int> others{1, 2, 3};
    subtract_from_all(others, others[1]);
    CHECK_EQ(others, {-1, 0, 1});
}

TEST("largest: points into the caller's vector") {
    std::vector<int> values{3, 8, 1, 8};
    CHECK(largest(values) == &values[1], "should point at values[1] itself, not into a copy");
}

TEST("largest: writing through the result") {
    std::vector<int> values{3, 8, 1, 8};
    int *top = largest(values);
    *top = 0;
    CHECK_EQ(values, {3, 0, 1, 8});
}

TEST("largest: negatives and one element") {
    std::vector<int> negatives{-5, -2, -8};
    CHECK(largest(negatives) == &negatives[1], "-2 is the largest: point at negatives[1]");
    std::vector<int> one{4};
    CHECK(largest(one) == &one[0], "with one element, point at values[0]");
}
