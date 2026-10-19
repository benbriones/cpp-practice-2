#include "grader.hpp"
#include "16_multi_file_programs/02_namespaces_and_linkage/textutils.hpp"

TEST("textutils::count_vowels") {
    CHECK_EQ(textutils::count_vowels("Hello World"), 3);
    CHECK_EQ(textutils::count_vowels("AEIOU aeiou"), 10);
    CHECK_EQ(textutils::count_vowels("rhythm"), 0);
}

TEST("textutils::count_vowel_words") {
    CHECK_EQ(textutils::count_vowel_words("an apple is on the table"), 4);
    CHECK_EQ(textutils::count_vowel_words("Every Other Thing"), 2);
    CHECK_EQ(textutils::count_vowel_words(""), 0);
}

TEST("textutils::strip_punctuation") {
    CHECK_EQ(textutils::strip_punctuation("Hi, there! (ok?)"), "Hi there ok");
    CHECK_EQ(textutils::strip_punctuation("plain"), "plain");
}

TEST("textutils::count_punctuation") {
    CHECK_EQ(textutils::count_punctuation("Wait... what?!"), 5);
    CHECK_EQ(textutils::count_punctuation("none here"), 0);
}

TEST("a using-declaration brings one name into scope") {
    using textutils::count_vowels;
    CHECK_EQ(count_vowels("queue"), 4);
}
