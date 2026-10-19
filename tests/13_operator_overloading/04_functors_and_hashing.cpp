#include "grader.hpp"
#include "13_operator_overloading/04_functors_and_hashing.cpp"

TEST("ByLength: shorter strings come first") {
    const ByLength less;
    CHECK(less("a", "bb"), "\"a\" should come before \"bb\"");
    CHECK(!less("bb", "a"), "\"bb\" should not come before \"a\"");
    CHECK(less("zz", "aaa"), "\"zz\" should come before \"aaa\" (shorter wins)");
}

TEST("ByLength: equal lengths are alphabetical") {
    const ByLength less;
    CHECK(less("aa", "ab"), "\"aa\" should come before \"ab\"");
    CHECK(!less("ab", "aa"), "\"ab\" should not come before \"aa\"");
    CHECK(!less("same", "same"), "a string should not come before itself");
}

TEST("sort_by_length") {
    std::vector<std::string> words{"ccc", "a", "bb", "aa", "b"};
    sort_by_length(words);
    CHECK_EQ(words, {"a", "b", "aa", "bb", "ccc"});
}

TEST("distinct_by_length: drops duplicates, keeps ByLength order") {
    CHECK_EQ(distinct_by_length({"pear", "fig", "apple", "fig", "kiwi", "pear"}),
             {"fig", "kiwi", "pear", "apple"});
    CHECK_EQ(distinct_by_length({}), {});
}

TEST("InRange: inclusive bounds") {
    const InRange teens{13, 19};
    CHECK(teens(13), "13 is in [13, 19]");
    CHECK(teens(19), "19 is in [13, 19]");
    CHECK(teens(15), "15 is in [13, 19]");
    CHECK(!teens(12), "12 is not in [13, 19]");
    CHECK(!teens(20), "20 is not in [13, 19]");
}

TEST("count_in_range") {
    CHECK_EQ(count_in_range({1, 5, 10, 15, 20}, 5, 15), 3);
    CHECK_EQ(count_in_range({-3, -2, 0, 2}, -2, 1), 2);
    CHECK_EQ(count_in_range({}, 0, 100), 0);
}

TEST("PointHash: equal points hash equal") {
    const PointHash hash;
    CHECK_EQ(hash(Point{3, 4}), hash(Point{3, 4}));
    CHECK_EQ(hash(Point{-7, 0}), hash(Point{-7, 0}));
}

TEST("PointHash: spreads points out") {
    const PointHash hash;
    std::set<std::size_t> hashes;
    for (int x = 0; x < 20; ++x) {
        for (int y = 0; y < 20; ++y) hashes.insert(hash(Point{x, y}));
    }
    CHECK(hashes.size() >= 390,
          std::format("a 20x20 grid gave only {} different hashes (need 390+)", hashes.size()));
    CHECK(hash(Point{1, 2}) != hash(Point{2, 1}), "(1, 2) and (2, 1) should hash differently");
}

TEST("count_distinct") {
    CHECK_EQ(count_distinct({{0, 0}, {1, 2}, {0, 0}, {2, 1}, {1, 2}}), 3);
    CHECK_EQ(count_distinct({{5, 5}}), 1);
    CHECK_EQ(count_distinct({}), 0);
}

TEST("most_visited") {
    CHECK_EQ(most_visited({{0, 0}, {1, 1}, {1, 1}, {2, 2}, {1, 1}, {0, 0}}), Point{1, 1});
    CHECK_EQ(most_visited({{7, -3}}), Point{7, -3});
}

TEST("most_visited: ties go to the first point in the list") {
    CHECK_EQ(most_visited({{2, 2}, {1, 1}, {1, 1}, {2, 2}}), Point{2, 2});
}

TEST("most_visited: empty list") {
    CHECK_EQ(most_visited({}), std::nullopt);
}
