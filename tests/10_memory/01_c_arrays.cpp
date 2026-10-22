#include "grader.hpp"
#include "10_memory/01_c_arrays.cpp"

TEST("find_first_even: returns the first even element") {
    int values[] = {7, 3, 8, 5, 4};
    CHECK_EQ(find_first_even(values, 5), &values[2]);
}

TEST("find_first_even: the pointer reaches the real element") {
    int values[] = {1, 6, 9};
    int *found = find_first_even(values, 3);
    CHECK(found != nullptr, "Expected a pointer to 6, got nullptr");
    *found = 0;
    CHECK_EQ(values[1], 0);
}

TEST("find_first_even: first element, negatives") {
    int starts_even[] = {2, 4, 6};
    CHECK_EQ(find_first_even(starts_even, 3), &starts_even[0]);
    int negatives[] = {-3, -4, 5};
    CHECK_EQ(find_first_even(negatives, 3), &negatives[1]);
}

TEST("find_first_even: no even element returns nullptr") {
    int odds[] = {1, 3, 5};
    CHECK_EQ(find_first_even(odds, 3), nullptr);
}

TEST("find_first_even: only looks at the first count elements") {
    int values[] = {1, 3, 4};
    CHECK_EQ(find_first_even(values, 2), nullptr);
    CHECK_EQ(find_first_even(values, 0), nullptr);
}

TEST("sum_array") {
    const int values[] = {1, 2, 3, 4};
    CHECK_EQ(sum_array(values, 4), 10);
    CHECK_EQ(sum_array(values, 2), 3);
    CHECK_EQ(sum_array(values, 0), 0);
}

TEST("reverse_array: odd and even lengths") {
    int odd[] = {1, 2, 3, 4, 5};
    reverse_array(odd, 5);
    CHECK_EQ(std::vector<int>(odd, odd + 5), {5, 4, 3, 2, 1});
    int even[] = {1, 2, 3, 4};
    reverse_array(even, 4);
    CHECK_EQ(std::vector<int>(even, even + 4), {4, 3, 2, 1});
}

TEST("reverse_array: only the first count elements") {
    int values[] = {1, 2, 3, 9, 9};
    reverse_array(values, 3);
    CHECK_EQ(std::vector<int>(values, values + 5), {3, 2, 1, 9, 9});
    reverse_array(values, 0);
    reverse_array(values, 1);
    CHECK_EQ(std::vector<int>(values, values + 5), {3, 2, 1, 9, 9});
}

TEST("count_in_range: whole array") {
    const int values[] = {5, 1, 9, 3, 7, 10};
    CHECK_EQ(count_in_range(values, values + 6, 3, 9), 4);
}

TEST("count_in_range: a slice of the array") {
    const int values[] = {5, 1, 9, 3, 7, 10};
    CHECK_EQ(count_in_range(values + 1, values + 4, 1, 5), 2);
    CHECK_EQ(count_in_range(values + 2, values + 2, 0, 100), 0);
}
