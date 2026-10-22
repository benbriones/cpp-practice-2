#include "grader.hpp"
#include "10_memory/02_c_strings.cpp"

// Where p points inside text (-1 for nullptr), so failures show positions, not strings.
long position(const char *p, const char *text) { return p == nullptr ? -1 : p - text; }

TEST("my_strlen") {
    CHECK_EQ(my_strlen("hello"), 5);
    CHECK_EQ(my_strlen("a"), 1);
    CHECK_EQ(my_strlen(""), 0);
}

TEST("my_strlen: stops at the first terminator") {
    const char text[] = {'a', 'b', '\0', 'c', 'd', '\0'};
    CHECK_EQ(my_strlen(text), 2);
}

TEST("my_strcmp: equal strings") {
    CHECK_EQ(my_strcmp("apple", "apple"), 0);
    CHECK_EQ(my_strcmp("", ""), 0);
}

TEST("my_strcmp: different strings") {
    CHECK(my_strcmp("apple", "banana") < 0, "my_strcmp(\"apple\", \"banana\") should be negative");
    CHECK(my_strcmp("banana", "apple") > 0, "my_strcmp(\"banana\", \"apple\") should be positive");
    CHECK(my_strcmp("abcd", "abce") < 0, "my_strcmp(\"abcd\", \"abce\") should be negative");
}

TEST("my_strcmp: one string is a prefix of the other") {
    CHECK(my_strcmp("app", "apple") < 0, "my_strcmp(\"app\", \"apple\") should be negative");
    CHECK(my_strcmp("apple", "app") > 0, "my_strcmp(\"apple\", \"app\") should be positive");
    CHECK(my_strcmp("", "a") < 0, "my_strcmp(\"\", \"a\") should be negative");
}

TEST("my_strcpy: copies the characters and the terminator") {
    char buffer[16];
    for (char &c : buffer) c = 'x';
    my_strcpy(buffer, "hello");
    CHECK_EQ(std::string(buffer), "hello");
    CHECK_EQ(buffer[5], '\0');
    CHECK_EQ(buffer[6], 'x');
}

TEST("my_strcpy: returns dest and handles empty strings") {
    char buffer[8] = "old";
    CHECK(my_strcpy(buffer, "") == buffer, "my_strcpy should return dest");
    CHECK_EQ(buffer[0], '\0');
}

TEST("find_char: points at the first match") {
    const char *text = "hello world";
    CHECK_EQ(position(find_char(text, 'o'), text), 4);
    CHECK_EQ(position(find_char(text, 'h'), text), 0);
    CHECK_EQ(position(find_char(text, 'd'), text), 10);
}

TEST("find_char: not found returns nullptr") {
    const char *text = "hello";
    CHECK_EQ(position(find_char(text, 'z'), text), -1);
    const char *empty = "";
    CHECK_EQ(position(find_char(empty, 'a'), empty), -1);
}
