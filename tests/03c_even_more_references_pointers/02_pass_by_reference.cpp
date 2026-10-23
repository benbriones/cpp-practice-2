#include "grader.hpp"
#include "03c_even_more_references_pointers/02_pass_by_reference.cpp"

namespace {

void transfer(int &from, int &to, int amount) {
    from -= amount;
    to += amount;
}

void sum_into(int &total, const int &a, const int &b) {
    total = a;
    total += b;
}

}  // namespace

TEST("trace_3: transfers, including to itself") {
    int x = 10;
    int y = 0;
    transfer(x, y, 3);
    transfer(y, x, 1);
    transfer(x, x, 5);
    CHECK_EQ(trace_3(), {x, y});
}

TEST("trace_4: sums with aliased parameters") {
    int x = 1;
    int y = 2;
    int z = 0;
    sum_into(z, x, y);
    sum_into(x, y, x);
    sum_into(y, y, y);
    CHECK_EQ(trace_4(), {x, y, z});
}

TEST("sort3: every starting order") {
    std::vector<std::vector<int>> orders{{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                         {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    for (const std::vector<int> &order : orders) {
        int a = order[0];
        int b = order[1];
        int c = order[2];
        sort3(a, b, c);
        CHECK_EQ(std::vector<int>{a, b, c}, {1, 2, 3});
    }
}

TEST("sort3: repeats and negatives") {
    int a = 5;
    int b = -2;
    int c = 5;
    sort3(a, b, c);
    CHECK_EQ(std::vector<int>{a, b, c}, {-2, 5, 5});
    int d = 0;
    int e = 0;
    int f = 0;
    sort3(d, e, f);
    CHECK_EQ(std::vector<int>{d, e, f}, {0, 0, 0});
}

TEST("sort3: vector elements") {
    std::vector<int> values{9, 4, 7};
    sort3(values[0], values[1], values[2]);
    CHECK_EQ(values, {4, 7, 9});
}

TEST("pop_word: takes words off the front") {
    std::string text = "to be or";
    std::string word = "old";
    CHECK_EQ(pop_word(text, word), true);
    CHECK_EQ(word, "to");
    CHECK_EQ(text, "be or");
    CHECK_EQ(pop_word(text, word), true);
    CHECK_EQ(word, "be");
    CHECK_EQ(text, "or");
}

TEST("pop_word: the last word empties text") {
    std::string text = "solo";
    std::string word;
    CHECK_EQ(pop_word(text, word), true);
    CHECK_EQ(word, "solo");
    CHECK_EQ(text, "");
}

TEST("pop_word: empty text leaves both alone") {
    std::string text;
    std::string word = "kept";
    CHECK_EQ(pop_word(text, word), false);
    CHECK_EQ(word, "kept");
    CHECK_EQ(text, "");
}

TEST("pop_word: in a loop") {
    std::string text = "a bb ccc";
    std::string word;
    std::vector<std::string> words;
    while (pop_word(text, word)) {
        words.push_back(word);
    }
    CHECK_EQ(words, {"a", "bb", "ccc"});
    CHECK_EQ(text, "");
}

TEST("append_copy: two different vectors") {
    std::vector<int> dest{1, 2};
    std::vector<int> src{3, 4};
    append_copy(dest, src);
    CHECK_EQ(dest, {1, 2, 3, 4});
    CHECK_EQ(src, {3, 4});
}

TEST("append_copy: empty on either side") {
    std::vector<int> dest;
    std::vector<int> src{5};
    append_copy(dest, src);
    CHECK_EQ(dest, {5});
    std::vector<int> empty;
    append_copy(dest, empty);
    CHECK_EQ(dest, {5});
}

TEST("append_copy: a vector appended to itself") {
    std::vector<int> values{1, 2, 3};
    append_copy(values, values);
    CHECK_EQ(values, {1, 2, 3, 1, 2, 3});
}

TEST("append_copy: itself, twice") {
    std::vector<int> values{7};
    append_copy(values, values);
    append_copy(values, values);
    CHECK_EQ(values, {7, 7, 7, 7});
    std::vector<int> empty;
    append_copy(empty, empty);
    CHECK(empty.empty());
}
