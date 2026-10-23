#include "grader.hpp"
#include "03b_more_references_pointers/01_addresses.cpp"

TEST("trace_1: a and b at the end") {
    int a = 1;
    int b = 2;
    int *p = &a;
    int &r = b;
    *p = 10;
    r = 20;
    p = &b;
    *p += 5;
    CHECK_EQ(trace_1(), {a, b});
}

TEST("trace_2: which statements are true") {
    // (1) same value  (3) a reference shares x's address  (5) both sides read 7
    CHECK_EQ(trace_2(), {1, 3, 5});
}

TEST("same_object: a variable and itself") {
    int x = 3;
    CHECK_EQ(same_object(x, x), true);
}

TEST("same_object: equal values in different variables") {
    int x = 3;
    int y = 3;
    CHECK(!same_object(x, y), "x and y both hold 3 but are different variables: compare addresses");
}

TEST("same_object: a reference and the variable it names") {
    int x = 3;
    int &r = x;
    CHECK_EQ(same_object(r, x), true);
    CHECK_EQ(same_object(x, r), true);
}

TEST("same_object: vector elements") {
    std::vector<int> values{5, 5, 5};
    CHECK_EQ(same_object(values[1], values[1]), true);
    CHECK_EQ(same_object(values[0], values[1]), false);
}

TEST("index_of: the element p points at") {
    std::vector<int> values{4, 8, 15};
    CHECK_EQ(index_of(values, &values[0]), 0);
    CHECK_EQ(index_of(values, &values[2]), 2);
}

TEST("index_of: compares addresses, not values") {
    std::vector<int> values{7, 7, 7};
    CHECK_EQ(index_of(values, &values[2]), 2);
    int outside = 7;
    CHECK_EQ(index_of(values, &outside), 3);
}

TEST("index_of: nullptr and an empty vector") {
    std::vector<int> values{1, 2};
    CHECK_EQ(index_of(values, nullptr), 2);
    std::vector<int> empty;
    int x = 1;
    CHECK_EQ(index_of(empty, &x), 0);
}

TEST("pointers_to_each: one pointer per element, in order") {
    std::vector<int> values{10, 20, 30};
    std::vector<int *> pointers = pointers_to_each(values);
    CHECK_EQ(pointers.size(), 3);
    for (std::size_t i = 0; i < values.size(); ++i) {
        CHECK(pointers[i] == &values[i], "result[i] should hold &values[i], the element's address");
    }
}

TEST("pointers_to_each: writing through a pointer changes the vector") {
    std::vector<int> values{1, 2, 3};
    std::vector<int *> pointers = pointers_to_each(values);
    *pointers[1] = 99;
    CHECK_EQ(values, {1, 99, 3});
}

TEST("pointers_to_each: changes to the vector show through the pointers") {
    std::vector<int> values{1, 2, 3};
    std::vector<int *> pointers = pointers_to_each(values);
    values[0] = 50;
    CHECK_EQ(*pointers[0], 50);
}

TEST("pointers_to_each: empty vector") {
    std::vector<int> values;
    CHECK(pointers_to_each(values).empty());
}
