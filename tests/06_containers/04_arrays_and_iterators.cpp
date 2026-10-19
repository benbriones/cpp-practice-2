#include "grader.hpp"
#include "06_containers/04_arrays_and_iterators.cpp"

TEST("letter_counts: counts each letter") {
    CHECK_EQ(letter_counts("abcab"), {2, 2, 1});
    std::array<int, 26> counts = letter_counts("zzz");
    CHECK_EQ(counts[25], 3);
    CHECK_EQ(counts[0], 0);
}

TEST("letter_counts: ignores case and non-letters") {
    CHECK_EQ(letter_counts("A a! B? 42"), {2, 1});
}

TEST("letter_counts: empty text is all zeros") {
    CHECK_EQ(letter_counts(""), {});
}

TEST("remove_below: erases low scores") {
    std::map<std::string, int> scores{{"ada", 90}, {"bob", 40}, {"cy", 75}, {"dee", 10}};
    remove_below(scores, 50);
    CHECK_EQ(scores, {{"ada", 90}, {"cy", 75}});
}

TEST("remove_below: threshold itself stays") {
    std::map<std::string, int> scores{{"ada", 50}, {"bob", 49}};
    remove_below(scores, 50);
    CHECK_EQ(scores, {{"ada", 50}});
}

TEST("remove_below: everything or nothing") {
    std::map<std::string, int> scores{{"ada", 1}, {"bob", 2}};
    remove_below(scores, 0);
    CHECK_EQ(scores.size(), 2);
    remove_below(scores, 100);
    CHECK_EQ(scores, {});
}

TEST("remove_short_words: keeps order") {
    std::vector<std::string> words{"a", "tree", "is", "tall", "and", "green"};
    remove_short_words(words, 4);
    CHECK_EQ(words, {"tree", "tall", "green"});
}

TEST("remove_short_words: adjacent short words") {
    std::vector<std::string> words{"x", "y", "z", "long", "q"};
    remove_short_words(words, 2);
    CHECK_EQ(words, {"long"});
}

TEST("remove_short_words: nothing to remove, or empty") {
    std::vector<std::string> words{"keep", "these"};
    remove_short_words(words, 1);
    CHECK_EQ(words, {"keep", "these"});
    std::vector<std::string> none;
    remove_short_words(none, 3);
    CHECK_EQ(none, {});
}

TEST("insert_sorted: middle") {
    std::vector<int> values{1, 3, 5};
    insert_sorted(values, 4);
    CHECK_EQ(values, {1, 3, 4, 5});
}

TEST("insert_sorted: front, back, and empty") {
    std::vector<int> values{2, 3};
    insert_sorted(values, 1);
    insert_sorted(values, 9);
    CHECK_EQ(values, {1, 2, 3, 9});
    std::vector<int> empty;
    insert_sorted(empty, 7);
    CHECK_EQ(empty, {7});
}

TEST("insert_sorted: duplicates") {
    std::vector<int> values{1, 2, 2, 3};
    insert_sorted(values, 2);
    CHECK_EQ(values, {1, 2, 2, 2, 3});
}
