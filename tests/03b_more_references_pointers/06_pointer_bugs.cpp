#include "grader.hpp"
#include "03b_more_references_pointers/06_pointer_bugs.cpp"

TEST("swap_values: exchanges the pointed-at ints") {
    int x = 1;
    int y = 2;
    swap_values(&x, &y);
    CHECK_EQ(x, 2);
    CHECK_EQ(y, 1);
}

TEST("swap_values: vector elements") {
    std::vector<int> values{10, 20, 30};
    swap_values(&values[0], &values[2]);
    CHECK_EQ(values, {30, 20, 10});
}

TEST("add_bonus: changes the caller's scores") {
    std::vector<int> scores{70, 85, 90};
    add_bonus(scores, 5);
    CHECK_EQ(scores, {75, 90, 95});
}

TEST("add_bonus: a negative bonus") {
    std::vector<int> scores{10};
    add_bonus(scores, -3);
    CHECK_EQ(scores, {7});
}

TEST("count_negatives: writes the count") {
    int count = -1;
    count_negatives({3, -1, 0, -7, 2}, &count);
    CHECK_EQ(count, 2);
}

TEST("count_negatives: none") {
    int count = -1;
    count_negatives({1, 2}, &count);
    CHECK_EQ(count, 0);
    count = -1;
    count_negatives({}, &count);
    CHECK_EQ(count, 0);
}

TEST("zero_largest: zeroes the largest, leaves the rest") {
    std::vector<int> values{3, 9, 5};
    zero_largest(values);
    CHECK_EQ(values, {3, 0, 5});
}

TEST("zero_largest: the first one on ties") {
    std::vector<int> values{4, 9, 9};
    zero_largest(values);
    CHECK_EQ(values, {4, 0, 9});
}

TEST("zero_largest: largest at the front, and negatives") {
    std::vector<int> front{9, 1, 2};
    zero_largest(front);
    CHECK_EQ(front, {0, 1, 2});
    std::vector<int> negatives{-5, -2, -8};
    zero_largest(negatives);
    CHECK_EQ(negatives, {-5, 0, -8});
}

TEST("count_filled: a slot pointing at 0 counts") {
    int zero = 0;
    int five = 5;
    CHECK_EQ(count_filled({&zero, &five}), 2);
}

TEST("count_filled: nullptr slots are empty") {
    int five = 5;
    CHECK_EQ(count_filled({nullptr, &five, nullptr}), 1);
    CHECK_EQ(count_filled({nullptr}), 0);
    CHECK_EQ(count_filled({}), 0);
}

TEST("bump_all: adds 1 to each int") {
    int x = 1;
    int y = 10;
    bump_all({&x, &y});
    CHECK_EQ(x, 2);
    CHECK_EQ(y, 11);
}

TEST("bump_all: skips nullptrs, bumps repeats twice") {
    int x = 0;
    bump_all({&x, nullptr, &x});
    CHECK_EQ(x, 2);
}

TEST("oldest: refers to the largest age") {
    std::vector<int> ages{30, 72, 45, 72};
    CHECK(&oldest(ages) == &ages[1], "oldest should return a reference to ages[1]");
}

TEST("birthday_for_oldest: the oldest gets a year older") {
    std::vector<int> ages{30, 72, 45};
    birthday_for_oldest(ages);
    CHECK_EQ(ages, {30, 73, 45});
}

TEST("birthday_for_oldest: only the first of a tie") {
    std::vector<int> ages{50, 50};
    birthday_for_oldest(ages);
    birthday_for_oldest(ages);
    CHECK_EQ(ages, {52, 50});
}
