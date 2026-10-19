#include "grader.hpp"
#include "06_containers/02_sets.cpp"

TEST("unique_sorted: removes duplicates and sorts") {
    CHECK_EQ(unique_sorted({3, 1, 3, 2}), {1, 2, 3});
    CHECK_EQ(unique_sorted({5, -2, 5, 5, -2, 0}), {-2, 0, 5});
}

TEST("unique_sorted: already unique, or empty") {
    CHECK_EQ(unique_sorted({1, 2, 3}), {1, 2, 3});
    CHECK_EQ(unique_sorted({}), {});
}

TEST("common_elements") {
    CHECK_EQ(common_elements({1, 2, 3, 4}, {3, 4, 5}), {3, 4});
    CHECK_EQ(common_elements({7, 7, 1}, {7}), {7});
}

TEST("common_elements: nothing shared") {
    CHECK_EQ(common_elements({1, 2}, {3, 4}), {});
    CHECK_EQ(common_elements({}, {1}), {});
}

TEST("has_duplicates") {
    CHECK_EQ(has_duplicates({"red", "green", "red"}), true);
    CHECK_EQ(has_duplicates({"red", "green", "blue"}), false);
}

TEST("has_duplicates: case matters, empty is fine") {
    CHECK_EQ(has_duplicates({"Red", "red"}), false);
    CHECK_EQ(has_duplicates({}), false);
}

TEST("has_duplicates: fast for large input") {
    std::vector<std::string> words;
    for (int i = 0; i < 100'000; ++i) words.push_back("w" + std::to_string(i));
    CHECK_EQ(has_duplicates(words), false);
    words.push_back("w12345");
    CHECK_EQ(has_duplicates(words), true);
}

TEST("first_repeated_char: finds the first repeat") {
    CHECK_EQ(first_repeated_char("abcbad"), 'b');
    CHECK_EQ(first_repeated_char("hello"), 'l');
    CHECK_EQ(first_repeated_char("a b"), std::nullopt);
    CHECK_EQ(first_repeated_char("a  b"), ' ');
}

TEST("first_repeated_char: nothing repeats") {
    CHECK_EQ(first_repeated_char("abc"), std::nullopt);
    CHECK_EQ(first_repeated_char(""), std::nullopt);
}
