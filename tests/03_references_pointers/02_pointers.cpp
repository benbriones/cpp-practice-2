#include "grader.hpp"
#include "03_references_pointers/02_pointers.cpp"

TEST("set_if_not_null: writes through the pointer") {
    int x = 1;
    set_if_not_null(&x, 42);
    CHECK_EQ(x, 42);
}

TEST("set_if_not_null: does nothing for nullptr") {
    set_if_not_null(nullptr, 42);  // passes as long as it doesn't crash
    CHECK(true);
}

TEST("swap_through: exchanges the pointed-at values") {
    int a = 1;
    int b = 2;
    swap_through(&a, &b);
    CHECK_EQ(a, 2);
    CHECK_EQ(b, 1);
}

TEST("swap_through: works on vector elements") {
    std::vector<int> values{10, 20, 30};
    swap_through(&values[0], &values[2]);
    CHECK_EQ(values, {30, 20, 10});
}

TEST("find_value: points at the matching element") {
    std::vector<int> values{4, 8, 15, 16};
    int* found = find_value(values, 15);
    CHECK(found != nullptr, "find_value returned nullptr, but 15 is in the vector");
    CHECK(found == &values[2], "should point at values[2] itself, not at a copy");
}

TEST("find_value: the first match") {
    std::vector<int> values{5, 7, 5};
    CHECK(find_value(values, 5) == &values[0], "should point at the FIRST 5 (values[0])");
}

TEST("find_value: writing through the result changes the vector") {
    std::vector<int> values{4, 8, 15, 16};
    *find_value(values, 8) = 0;
    CHECK_EQ(values, {4, 0, 15, 16});
}

TEST("find_value: nullptr when missing") {
    std::vector<int> values{1, 2, 3};
    CHECK_EQ(find_value(values, 99), nullptr);
    std::vector<int> empty;
    CHECK_EQ(find_value(empty, 1), nullptr);
}

TEST("safe_divide: stores the quotient") {
    int result = 0;
    CHECK_EQ(safe_divide(7, 2, &result), true);
    CHECK_EQ(result, 3);
    CHECK_EQ(safe_divide(-9, 3, &result), true);
    CHECK_EQ(result, -3);
}

TEST("safe_divide: dividing by zero leaves the result alone") {
    int result = 123;
    CHECK_EQ(safe_divide(5, 0, &result), false);
    CHECK_EQ(result, 123);
}

TEST("sum_pointed: sums what the pointers point at") {
    int a = 1;
    int b = 20;
    int c = 300;
    CHECK_EQ(sum_pointed({&a, &b, &c}), 321);
    CHECK_EQ(sum_pointed({&a, &a}), 2);
}

TEST("sum_pointed: skips null pointers") {
    int a = 5;
    CHECK_EQ(sum_pointed({nullptr, &a, nullptr}), 5);
    CHECK_EQ(sum_pointed({nullptr}), 0);
    CHECK_EQ(sum_pointed({}), 0);
}

TEST("sum_pointed: sees changes made after the pointers were taken") {
    int a = 1;
    int b = 2;
    std::vector<const int*> pointers{&a, &b};
    a = 100;
    CHECK_EQ(sum_pointed(pointers), 102);
}
