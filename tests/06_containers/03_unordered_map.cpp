#include "grader.hpp"
#include "06_containers/03_unordered_map.cpp"

using IndexPair = std::pair<std::size_t, std::size_t>;

TEST("two_sum: finds a pair") {
    CHECK_EQ(two_sum({2, 7, 11, 15}, 9), IndexPair{0, 1});
    CHECK_EQ(two_sum({3, 2, 4}, 6), IndexPair{1, 2});
}

TEST("two_sum: can use the same value twice, but not the same index") {
    CHECK_EQ(two_sum({3, 3}, 6), IndexPair{0, 1});
    CHECK_EQ(two_sum({3, 5}, 6), std::nullopt);
}

TEST("two_sum: picks the smallest j, then the smallest i") {
    CHECK_EQ(two_sum({1, 4, 4, 3, 0}, 4), IndexPair{0, 3});
    CHECK_EQ(two_sum({2, 2, 2}, 4), IndexPair{0, 1});
}

TEST("two_sum: negatives and no answer") {
    CHECK_EQ(two_sum({-3, 8, 5}, 2), IndexPair{0, 2});
    CHECK_EQ(two_sum({1, 2, 3}, 100), std::nullopt);
    CHECK_EQ(two_sum({}, 0), std::nullopt);
}

TEST("two_sum: fast on large input") {
    std::vector<int> values;
    for (int i = 0; i < 200'000; ++i) values.push_back(2 * i);
    values.push_back(1);
    values.push_back(-1);
    CHECK_EQ(two_sum(values, 0), IndexPair{200'000, 200'001});
}

TEST("first_unique_char") {
    CHECK_EQ(first_unique_char("swiss"), 1);
    CHECK_EQ(first_unique_char("leetcode"), 0);
    CHECK_EQ(first_unique_char("aabbc"), 4);
}

TEST("first_unique_char: no unique character") {
    CHECK_EQ(first_unique_char("aabb"), std::nullopt);
    CHECK_EQ(first_unique_char(""), std::nullopt);
}

TEST("group_anagrams: groups in order of first appearance") {
    CHECK_EQ(group_anagrams({"eat", "tea", "tan", "ate", "nat", "bat"}),
             {{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}});
}

TEST("group_anagrams: no anagrams at all") {
    CHECK_EQ(group_anagrams({"one", "two"}), {{"one"}, {"two"}});
}

TEST("group_anagrams: repeated words and empty input") {
    CHECK_EQ(group_anagrams({"ab", "ba", "ab"}), {{"ab", "ba", "ab"}});
    CHECK_EQ(group_anagrams({}), {});
}
