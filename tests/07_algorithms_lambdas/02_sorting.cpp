#include "grader.hpp"
#include "07_algorithms_lambdas/02_sorting.cpp"

static std::vector<std::string> names_of(const std::vector<Person>& people) {
    std::vector<std::string> names;
    for (const auto& person : people) names.push_back(person.name);
    return names;
}

TEST("sort_descending") {
    CHECK_EQ(sort_descending({3, 1, 4, 1, 5, 9, 2, 6}), {9, 6, 5, 4, 3, 2, 1, 1});
    CHECK_EQ(sort_descending({-1, -10, 0}), {0, -1, -10});
    CHECK_EQ(sort_descending({}), {});
}

TEST("sort_by_length: shortest first") {
    CHECK_EQ(sort_by_length({"ccc", "a", "bb"}), {"a", "bb", "ccc"});
}

TEST("sort_by_length: equal lengths keep their order") {
    CHECK_EQ(sort_by_length({"ccc", "b", "dd", "a", "bb"}), {"b", "a", "dd", "bb", "ccc"});
}

TEST("sort_by_length: stable on a long list") {
    // 60 words cycling through lengths 1, 2, 3; each length group is already in order.
    std::vector<std::string> words;
    std::vector<std::string> expected;
    for (int length = 1; length <= 3; ++length) {
        for (int i = 0; i < 20; ++i) {
            expected.push_back(std::string(static_cast<std::size_t>(length), static_cast<char>('a' + i)));
        }
    }
    for (int i = 0; i < 20; ++i) {
        for (int length = 3; length >= 1; --length) {
            words.push_back(std::string(static_cast<std::size_t>(length), static_cast<char>('a' + i)));
        }
    }
    CHECK_EQ(sort_by_length(words), expected);
}

TEST("sort_people: by age") {
    std::vector<Person> people{{"Cara", 41}, {"Abe", 19}, {"Bob", 30}};
    sort_people(people);
    CHECK_EQ(names_of(people), {"Abe", "Bob", "Cara"});
}

TEST("sort_people: same age sorted by name") {
    std::vector<Person> people{{"Cara", 30}, {"Abe", 25}, {"Bob", 30}, {"Dan", 25}, {"Ann", 30}};
    sort_people(people);
    CHECK_EQ(names_of(people), {"Abe", "Dan", "Ann", "Bob", "Cara"});
}

TEST("sort_ignoring_case") {
    CHECK_EQ(sort_ignoring_case({"banana", "Cherry", "apple", "Date"}),
             {"apple", "banana", "Cherry", "Date"});
    CHECK_EQ(sort_ignoring_case({"b", "A", "c", "B2"}), {"A", "b", "B2", "c"});
}

TEST("top_n: largest first") {
    CHECK_EQ(top_n({5, 1, 9, 3, 7}, 3), {9, 7, 5});
    CHECK_EQ(top_n({5, 1, 9, 3, 7}, 1), {9});
}

TEST("top_n: zero, or more than there are") {
    CHECK_EQ(top_n({5, 1, 9}, 0), {});
    CHECK_EQ(top_n({5, 1, 9}, 10), {9, 5, 1});
    CHECK_EQ(top_n({}, 2), {});
}
