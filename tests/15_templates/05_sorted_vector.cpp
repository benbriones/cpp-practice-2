#include "grader.hpp"
#include "15_templates/05_sorted_vector.cpp"

#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

template <class T, class C>
std::vector<T> contents(const SortedVector<T, C> &sorted) {
    return std::vector<T>(sorted.begin(), sorted.end());
}

TEST("insert keeps elements sorted") {
    SortedVector<int> sorted;
    for (int x : {5, 1, 4, 1, 3}) sorted.insert(x);
    CHECK_EQ(contents(sorted), {1, 1, 3, 4, 5});
    CHECK_EQ(sorted.size(), 5);
}

TEST("initializer list constructor sorts its values") {
    SortedVector<int> sorted{3, 1, 2};
    CHECK_EQ(contents(sorted), {1, 2, 3});
}

TEST("a default-constructed SortedVector is empty") {
    SortedVector<int> sorted;
    CHECK_EQ(sorted.size(), 0);
    CHECK(sorted.begin() == sorted.end());
}

TEST("operator[] reads by position") {
    SortedVector<std::string> sorted{"pear", "apple", "fig"};
    CHECK_EQ(sorted[0], "apple");
    CHECK_EQ(sorted[1], "fig");
    CHECK_EQ(sorted[2], "pear");
}

TEST("contains") {
    SortedVector<int> sorted{10, 30, 20};
    CHECK(sorted.contains(20));
    CHECK(sorted.contains(10));
    CHECK(sorted.contains(30));
    CHECK(!sorted.contains(25));
    CHECK(!sorted.contains(5));
    CHECK(!sorted.contains(99));
    CHECK(!SortedVector<int>{}.contains(1));
}

TEST("count counts duplicates") {
    SortedVector<int> sorted{2, 2, 1, 2, 3};
    CHECK_EQ(sorted.count(2), 3);
    CHECK_EQ(sorted.count(1), 1);
    CHECK_EQ(sorted.count(7), 0);
}

TEST("erase removes one matching element") {
    SortedVector<int> sorted{1, 2, 2, 3};
    CHECK(sorted.erase(2));
    CHECK_EQ(contents(sorted), {1, 2, 3});
    CHECK(!sorted.erase(9));
    CHECK_EQ(sorted.size(), 3);
}

TEST("std::greater sorts descending") {
    SortedVector<int, std::greater<int>> sorted{1, 3, 2};
    sorted.insert(5);
    CHECK_EQ(contents(sorted), {5, 3, 2, 1});
    CHECK(sorted.contains(2));
    CHECK(!sorted.contains(4));
}

TEST("custom comparator: equal keys stay in insertion order") {
    struct Task {
        int priority;
        std::string name;
    };
    struct ByPriority {
        bool operator()(const Task &a, const Task &b) const { return a.priority < b.priority; }
    };
    SortedVector<Task, ByPriority> tasks;
    tasks.insert({2, "write"});
    tasks.insert({1, "plan"});
    tasks.insert({2, "test"});
    tasks.insert({1, "think"});
    std::vector<std::string> names;
    for (const Task &task : tasks) names.push_back(task.name);
    CHECK_EQ(names, {"plan", "think", "write", "test"});
}

TEST("works with range-for and algorithms") {
    SortedVector<int> sorted{4, 1, 3};
    int total = 0;
    for (int x : sorted) total += x;
    CHECK_EQ(total, 8);
    CHECK_EQ(std::accumulate(sorted.begin(), sorted.end(), 0), 8);
    CHECK_EQ(*std::max_element(sorted.begin(), sorted.end()), 4);
}

TEST("iterators are read-only") {
    SortedVector<int> sorted{1};
    CHECK_EQ(*sorted.begin(), 1);
    CHECK((std::is_same_v<decltype(*sorted.begin()), const int &>),
          "begin() should return a const_iterator");
}

TEST("insert and contains use binary search (50,000 elements)") {
    SortedVector<int> sorted;
    for (int i = 0; i < 50'000; ++i) sorted.insert(i * 2);
    int found = 0;
    for (int i = 0; i < 100'000; ++i) {
        if (sorted.contains(i)) ++found;
    }
    CHECK_EQ(found, 50'000);
}
