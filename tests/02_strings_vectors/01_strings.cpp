#include "grader.hpp"
#include "02_strings_vectors/01_strings.cpp"

TEST("count_char: counts every occurrence") {
    CHECK_EQ(count_char("banana", 'a'), 3);
    CHECK_EQ(count_char("banana", 'n'), 2);
    CHECK_EQ(count_char("mississippi", 's'), 4);
}

TEST("count_char: none or empty") {
    CHECK_EQ(count_char("banana", 'z'), 0);
    CHECK_EQ(count_char("", 'a'), 0);
}

TEST("count_char: case-sensitive") {
    CHECK_EQ(count_char("Aardvark", 'a'), 2);
}

TEST("reverse_string") {
    CHECK_EQ(reverse_string("abc"), "cba");
    CHECK_EQ(reverse_string("racecar"), "racecar");
    CHECK_EQ(reverse_string("Hello, world"), "dlrow ,olleH");
}

TEST("reverse_string: short strings") {
    CHECK_EQ(reverse_string(""), "");
    CHECK_EQ(reverse_string("x"), "x");
}

TEST("is_palindrome: simple words") {
    CHECK_EQ(is_palindrome("racecar"), true);
    CHECK_EQ(is_palindrome("abba"), true);
    CHECK_EQ(is_palindrome("abca"), false);
}

TEST("is_palindrome: ignores case") {
    CHECK_EQ(is_palindrome("RaceCar"), true);
}

TEST("is_palindrome: ignores punctuation and spaces") {
    CHECK_EQ(is_palindrome("A man, a plan, a canal: Panama!"), true);
    CHECK_EQ(is_palindrome("Was it a car or a cat I saw?"), true);
    CHECK_EQ(is_palindrome("Not a palindrome."), false);
}

TEST("is_palindrome: empty and single letters") {
    CHECK_EQ(is_palindrome(""), true);
    CHECK_EQ(is_palindrome("a"), true);
    CHECK_EQ(is_palindrome("?!"), true);
}

TEST("initials: lower-case names") {
    CHECK_EQ(initials("ada king lovelace"), "AKL");
    CHECK_EQ(initials("grace hopper"), "GH");
}

TEST("initials: already capitalised, single word") {
    CHECK_EQ(initials("Alan Turing"), "AT");
    CHECK_EQ(initials("plato"), "P");
}

TEST("initials: extra spaces") {
    CHECK_EQ(initials("  linus   torvalds "), "LT");
    CHECK_EQ(initials(""), "");
    CHECK_EQ(initials("   "), "");
}
