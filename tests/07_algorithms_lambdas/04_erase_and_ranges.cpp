#include "grader.hpp"
#include "07_algorithms_lambdas/04_erase_and_ranges.cpp"

TEST("remove_negatives") {
    std::vector<int> values{3, -1, 4, -1, -5, 9};
    remove_negatives(values);
    CHECK_EQ(values, {3, 4, 9});
}

TEST("remove_negatives: all or nothing to remove") {
    std::vector<int> all_negative{-1, -2};
    remove_negatives(all_negative);
    CHECK_EQ(all_negative, {});
    std::vector<int> none{0, 1, 2};
    remove_negatives(none);
    CHECK_EQ(none, {0, 1, 2});
}

TEST("remove_short_words") {
    std::vector<std::string> words{"a", "tree", "is", "green", "and", "tall"};
    remove_short_words(words, 4);
    CHECK_EQ(words, {"tree", "green", "tall"});
}

TEST("remove_short_words: minimum of 0 keeps everything") {
    std::vector<std::string> words{"", "x"};
    remove_short_words(words, 0);
    CHECK_EQ(words, {"", "x"});
}

TEST("dedupe") {
    CHECK_EQ(dedupe({3, 1, 3, 2, 1}), {1, 2, 3});
    CHECK_EQ(dedupe({5, 5, 5}), {5});
    CHECK_EQ(dedupe({-2, 7, -2, 0}), {-2, 0, 7});
    CHECK_EQ(dedupe({}), {});
}

TEST("squeeze") {
    CHECK_EQ(squeeze("aaabccdddd"), "abcd");
    CHECK_EQ(squeeze("mississippi"), "misisipi");
    CHECK_EQ(squeeze("abc"), "abc");
    CHECK_EQ(squeeze(""), "");
}

TEST("first_n_even_squares") {
    CHECK_EQ(first_n_even_squares({1, 2, 3, 4, 5, 6}, 2), {4, 16});
    CHECK_EQ(first_n_even_squares({10, 7, -2, 0}, 3), {100, 4, 0});
}

TEST("first_n_even_squares: fewer evens than asked for") {
    CHECK_EQ(first_n_even_squares({1, 2, 3}, 5), {4});
    CHECK_EQ(first_n_even_squares({1, 3, 5}, 2), {});
    CHECK_EQ(first_n_even_squares({2, 4}, 0), {});
}
