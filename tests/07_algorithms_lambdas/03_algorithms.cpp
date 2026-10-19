#include "grader.hpp"
#include "07_algorithms_lambdas/03_algorithms.cpp"

TEST("count_longer_than") {
    const std::vector<std::string> words{"a", "tree", "is", "green", "and", "tall"};
    CHECK_EQ(count_longer_than(words, 3), 3);
    CHECK_EQ(count_longer_than(words, 0), 6);
    CHECK_EQ(count_longer_than(words, 10), 0);
    CHECK_EQ(count_longer_than({}, 1), 0);
}

TEST("first_negative_index") {
    CHECK_EQ(first_negative_index({4, 2, -1, 8, -5}), 2);
    CHECK_EQ(first_negative_index({-3, 1}), 0);
}

TEST("first_negative_index: none found") {
    CHECK_EQ(first_negative_index({1, 2, 3}), -1);
    CHECK_EQ(first_negative_index({0}), -1);
    CHECK_EQ(first_negative_index({}), -1);
}

TEST("all_positive") {
    CHECK_EQ(all_positive({1, 2, 3}), true);
    CHECK_EQ(all_positive({1, 0, 3}), false);
    CHECK_EQ(all_positive({-1}), false);
    CHECK_EQ(all_positive({}), true);
}

TEST("any_contains") {
    const std::vector<std::string> words{"cat", "dog", "bird"};
    CHECK_EQ(any_contains(words, 'o'), true);
    CHECK_EQ(any_contains(words, 'z'), false);
    CHECK_EQ(any_contains({}, 'a'), false);
}

TEST("product") {
    CHECK_EQ(product({1, 2, 3, 4}), 24);
    CHECK_EQ(product({-2, 5}), -10);
    CHECK_EQ(product({7, 0, 9}), 0);
    CHECK_EQ(product({}), 1);
}

TEST("product: bigger than an int") {
    CHECK_EQ(product({100'000, 100'000}), 10'000'000'000LL);
    CHECK_EQ(product({1'000, 1'000, 1'000, 1'000}), 1'000'000'000'000LL);
}

TEST("squares") {
    CHECK_EQ(squares({1, -2, 3}), {1, 4, 9});
    CHECK_EQ(squares({}), {});
}

TEST("spread") {
    CHECK_EQ(spread({3, 9, 1, 4}), 8);
    CHECK_EQ(spread({-5, 5}), 10);
    CHECK_EQ(spread({7}), 0);
    CHECK_EQ(spread({}), 0);
}
