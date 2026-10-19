#include "grader.hpp"
#include "15_templates/01_function_templates.cpp"

#include <array>
#include <set>
#include <string>

TEST("largest: ints and doubles") {
    CHECK_EQ(largest(std::vector<int>{3, 9, 2}), 9);
    CHECK_EQ(largest(std::vector<int>{-5, -2, -9}), -2);
    CHECK_NEAR(largest(std::vector<double>{1.5, 0.25, 1.75}), 1.75);
}

TEST("largest: strings compare alphabetically") {
    CHECK_EQ(largest(std::vector<std::string>{"pear", "apple", "zucchini", "fig"}), "zucchini");
}

TEST("largest: a single element") {
    CHECK_EQ(largest(std::vector<char>{'q'}), 'q');
}

TEST("largest: empty vector throws std::invalid_argument") {
    CHECK_THROWS(std::invalid_argument, largest(std::vector<int>{}));
}

TEST("count_matching: ints") {
    CHECK_EQ(count_matching(std::vector<int>{1, 2, 1, 3, 1}, 1), 3);
    CHECK_EQ(count_matching(std::vector<int>{1, 2, 3}, 7), 0);
    CHECK_EQ(count_matching(std::vector<int>{}, 7), 0);
}

TEST("count_matching: strings and chars") {
    const std::vector<std::string> words{"the", "cat", "the", "hat"};
    CHECK_EQ(count_matching(words, std::string("the")), 2);
    CHECK_EQ(count_matching(std::vector<char>{'a', 'b', 'a'}, 'a'), 2);
}

TEST("swap_values: ints") {
    int a = 1;
    int b = 2;
    swap_values(a, b);
    CHECK_EQ(a, 2);
    CHECK_EQ(b, 1);
}

TEST("swap_values: strings and vectors") {
    std::string first = "left";
    std::string second = "right";
    swap_values(first, second);
    CHECK_EQ(first, "right");
    CHECK_EQ(second, "left");
    std::vector<int> small{1};
    std::vector<int> big{1, 2, 3};
    swap_values(small, big);
    CHECK_EQ(small, {1, 2, 3});
    CHECK_EQ(big, {1});
}

TEST("invert: swaps keys and values") {
    const std::map<std::string, int> ids{{"ann", 1}, {"bob", 2}};
    CHECK_EQ(invert(ids), {{1, "ann"}, {2, "bob"}});
}

TEST("invert: shared values keep the last key") {
    const std::map<std::string, int> sizes{{"ant", 1}, {"bee", 1}, {"cow", 3}};
    CHECK_EQ(invert(sizes), {{1, "bee"}, {3, "cow"}});
}

TEST("invert: empty map") {
    CHECK_EQ(invert(std::map<int, char>{}), {});
}

TEST("sum: vectors of numbers") {
    CHECK_EQ(sum(std::vector<int>{1, 2, 3, 4}), 10);
    CHECK_NEAR(sum(std::vector<double>{0.5, 0.25}), 0.75);
}

TEST("sum: std::array and std::set") {
    const std::array<int, 3> trio{1, 2, 3};
    CHECK_EQ(sum(trio), 6);
    const std::set<int> unique{5, 5, 10};
    CHECK_EQ(sum(unique), 15);
}

TEST("sum: empty container is zero") {
    CHECK_EQ(sum(std::vector<int>{}), 0);
}

TEST("sum: strings concatenate") {
    CHECK_EQ(sum(std::vector<std::string>{"ab", "cd", "e"}), "abcde");
}
