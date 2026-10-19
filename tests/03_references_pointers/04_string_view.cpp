#include "grader.hpp"
#include "03_references_pointers/04_string_view.cpp"

#include <string>

TEST("count_words") {
    CHECK_EQ(count_words("one two three"), 3);
    CHECK_EQ(count_words("  hi \t there\n"), 2);
    CHECK_EQ(count_words("single"), 1);
}

TEST("count_words: no words") {
    CHECK_EQ(count_words(""), 0);
    CHECK_EQ(count_words(" \t\n "), 0);
}

TEST("first_word") {
    CHECK_EQ(first_word("hello world"), "hello");
    CHECK_EQ(first_word("  \tindented text"), "indented");
    CHECK_EQ(first_word("alone"), "alone");
}

TEST("first_word: no words") {
    CHECK(first_word("").empty(), "first_word(\"\") should be empty");
    CHECK(first_word("   ").empty(), "first_word(\"   \") should be empty");
}

TEST("first_word: is a view into the original text") {
    const std::string text = "  hello world";
    std::string_view word = first_word(text);
    CHECK_EQ(word, "hello");
    CHECK(word.data() == text.data() + 2, "the result should point into the original string");
}

TEST("trim_view") {
    CHECK_EQ(trim_view("  padded  "), "padded");
    CHECK_EQ(trim_view("\n\tboth sides \t"), "both sides");
    CHECK_EQ(trim_view("clean"), "clean");
}

TEST("trim_view: only whitespace or empty") {
    CHECK(trim_view("   ").empty(), "trim_view(\"   \") should be empty");
    CHECK(trim_view("").empty(), "trim_view(\"\") should be empty");
}

TEST("trim_view: is a view into the original text") {
    const std::string text = "   middle   ";
    std::string_view trimmed = trim_view(text);
    CHECK_EQ(trimmed, "middle");
    CHECK(trimmed.data() == text.data() + 3, "the result should point into the original string");
}

TEST("strip_prefix: prefix present") {
    CHECK_EQ(strip_prefix("unhappy", "un"), "happy");
    CHECK_EQ(strip_prefix("https://example.com", "https://"), "example.com");
    CHECK_EQ(strip_prefix("same", "same"), "");
}

TEST("strip_prefix: prefix absent") {
    CHECK_EQ(strip_prefix("happy", "un"), "happy");
    CHECK_EQ(strip_prefix("un", "unhappy"), "un");
    CHECK_EQ(strip_prefix("text", ""), "text");
}

TEST("strip_prefix: is a view into the original text") {
    const std::string text = "Mr. Smith";
    std::string_view rest = strip_prefix(text, "Mr. ");
    CHECK(rest.data() == text.data() + 4, "the result should point into the original string");
}
