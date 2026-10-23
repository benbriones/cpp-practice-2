#include "grader.hpp"
#include "03c_even_more_references_pointers/03_const_references.cpp"

TEST("trace_5: which calls compile") {
    // (2) and (4) need a plain & to bind to a const or a temporary; (5) needs int* from const int*
    CHECK_EQ(trace_5(), {1, 3, 6, 7, 8});
}

TEST("is_palindrome: palindromes") {
    CHECK_EQ(is_palindrome("racecar"), true);
    CHECK_EQ(is_palindrome("abba"), true);
    CHECK_EQ(is_palindrome("a"), true);
    CHECK_EQ(is_palindrome(""), true);
}

TEST("is_palindrome: not palindromes") {
    CHECK_EQ(is_palindrome("abca"), false);
    CHECK_EQ(is_palindrome("ab"), false);
    CHECK_EQ(is_palindrome("Aa"), false);
}

TEST("is_palindrome: spaces count") {
    CHECK_EQ(is_palindrome("a b a"), true);
    CHECK_EQ(is_palindrome("ab a"), false);
}

TEST("is_palindrome: temporaries and const strings") {
    std::string first = "ab";
    CHECK_EQ(is_palindrome(first + "ba"), true);
    CHECK_EQ(is_palindrome(first + "ab"), false);
    const std::string level = "level";
    CHECK_EQ(is_palindrome(level), true);
}

TEST("most_common: refers to the element itself") {
    std::vector<int> values{2, 7, 7, 3};
    const int &m = most_common(values);
    CHECK_EQ(m, 7);
    CHECK(&m == &values[1], "should refer to values[1], the first 7, not to a copy");
}

TEST("most_common: ties go to the value seen first") {
    std::vector<int> values{4, 1, 4, 2, 1};
    CHECK(&most_common(values) == &values[0], "4 and 1 tie, and 4 comes first: refer to values[0]");
    std::vector<int> later{1, 2, 2, 1};
    CHECK(&most_common(later) == &later[0], "1 and 2 tie, and 1 comes first: refer to later[0]");
}

TEST("most_common: the winner's first occurrence") {
    std::vector<int> values{5, 9, 5, 9, 9};
    CHECK(&most_common(values) == &values[1], "9 appears three times: refer to its first one, values[1]");
}

TEST("most_common: all different, and one element") {
    std::vector<int> values{3, 1, 2};
    CHECK(&most_common(values) == &values[0], "every count is 1, so refer to values[0]");
    std::vector<int> one{-6};
    CHECK(&most_common(one) == &one[0], "with one element, refer to values[0]");
}

TEST("find_by_prefix: points at the first match") {
    std::vector<std::string> words{"banana", "apple", "apricot"};
    const std::string *found = find_by_prefix(words, "ap");
    CHECK(found != nullptr, "find_by_prefix returned nullptr, but \"apple\" starts with \"ap\"");
    CHECK(found == &words[1], "should point at words[1] itself, not at a copy");
    CHECK(find_by_prefix(words, "apr") == &words[2], "only \"apricot\" starts with \"apr\"");
}

TEST("find_by_prefix: nullptr when nothing matches") {
    std::vector<std::string> words{"banana", "apple"};
    CHECK_EQ(find_by_prefix(words, "cherry"), nullptr);
    CHECK_EQ(find_by_prefix(words, "nana"), nullptr);
    CHECK_EQ(find_by_prefix(words, "bananas"), nullptr);
    std::vector<std::string> empty;
    CHECK_EQ(find_by_prefix(empty, "a"), nullptr);
}

TEST("find_by_prefix: whole words and an empty prefix") {
    std::vector<std::string> words{"car", "cart"};
    CHECK(find_by_prefix(words, "car") == &words[0], "a word equal to prefix counts");
    CHECK(find_by_prefix(words, "") == &words[0], "an empty prefix matches the first word");
}

TEST("find_by_prefix: case matters") {
    std::vector<std::string> words{"Apple", "apple"};
    CHECK(find_by_prefix(words, "app") == &words[1], "\"Apple\" doesn't start with \"app\"");
}
