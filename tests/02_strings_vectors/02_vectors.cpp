#include "grader.hpp"
#include "02_strings_vectors/02_vectors.cpp"

TEST("sum") {
    CHECK_EQ(sum({1, 2, 3, 4}), 10);
    CHECK_EQ(sum({-5, 5, 10}), 10);
    CHECK_EQ(sum({}), 0);
}

TEST("mean: keeps the fraction") {
    CHECK_NEAR(mean({1, 2, 3, 4}), 2.5);
    CHECK_NEAR(mean({7}), 7.0);
    CHECK_NEAR(mean({-1, 2}), 0.5);
}

TEST("mean: empty vector") {
    CHECK_NEAR(mean({}), 0.0);
}

TEST("evens: keeps order") {
    CHECK_EQ(evens({1, 2, 3, 4, 5, 6}), {2, 4, 6});
    CHECK_EQ(evens({8, 3, 0, -2}), {8, 0, -2});
}

TEST("evens: none or empty") {
    CHECK_EQ(evens({1, 3, 5}), {});
    CHECK_EQ(evens({}), {});
}

TEST("evens: leaves its input alone") {
    const std::vector<int> input{1, 2, 3};
    evens(input);
    CHECK_EQ(input, {1, 2, 3});
}

TEST("index_of_max") {
    CHECK_EQ(index_of_max({3, 9, 2}), 1);
    CHECK_EQ(index_of_max({9, 3, 2}), 0);
    CHECK_EQ(index_of_max({3, 2, 9}), 2);
}

TEST("index_of_max: negatives and duplicates") {
    CHECK_EQ(index_of_max({-5, -2, -9}), 1);
    CHECK_EQ(index_of_max({4, 7, 7, 1}), 1);
}

TEST("index_of_max: empty vector") {
    CHECK_EQ(index_of_max({}), -1);
}

TEST("running_total") {
    CHECK_EQ(running_total({1, 2, 3, 4}), {1, 3, 6, 10});
    CHECK_EQ(running_total({5, -5, 5}), {5, 0, 5});
    CHECK_EQ(running_total({}), {});
}
