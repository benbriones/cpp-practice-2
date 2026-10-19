#include "grader.hpp"
#include "09_streams_files/02_reading_files.cpp"

TEST("count_lines: lines ending in newlines") {
    grader::write_file("poem.txt", "roses\nviolets\nsugar\n");
    CHECK_EQ(count_lines("poem.txt"), 3);
}

TEST("count_lines: last line without a newline, blank lines, empty file") {
    grader::write_file("no_newline.txt", "one\ntwo");
    CHECK_EQ(count_lines("no_newline.txt"), 2);
    grader::write_file("blanks.txt", "a\n\n\nb\n");
    CHECK_EQ(count_lines("blanks.txt"), 4);
    grader::write_file("empty.txt", "");
    CHECK_EQ(count_lines("empty.txt"), 0);
}

TEST("count_lines: missing file throws std::runtime_error") {
    CHECK_THROWS(std::runtime_error, count_lines("does_not_exist.txt"));
}

TEST("read_lines: keeps blank lines, drops newlines") {
    grader::write_file("notes.txt", "first\n\n  indented\nlast");
    CHECK_EQ(read_lines("notes.txt"), {"first", "", "  indented", "last"});
}

TEST("read_lines: empty file") {
    grader::write_file("empty.txt", "");
    CHECK_EQ(read_lines("empty.txt"), {});
}

TEST("read_lines: error message names the file") {
    try {
        read_lines("missing.txt");
        CHECK(false, "Expected read_lines(\"missing.txt\") to throw std::runtime_error");
    } catch (const std::runtime_error& e) {
        CHECK_EQ(std::string(e.what()), "can't open missing.txt");
    }
}

TEST("word_counts_in_file: counts across lines") {
    grader::write_file("words.txt", "the cat\nthe  hat\n\nThe end.\n");
    CHECK_EQ(word_counts_in_file("words.txt"),
             {{"The", 1}, {"cat", 1}, {"end.", 1}, {"hat", 1}, {"the", 2}});
}

TEST("word_counts_in_file: empty file, missing file") {
    grader::write_file("empty.txt", "");
    CHECK_EQ(word_counts_in_file("empty.txt"), {});
    CHECK_THROWS(std::runtime_error, word_counts_in_file("nope.txt"));
}

TEST("sum_numbers_in_file: integers and decimals") {
    grader::write_file("numbers.txt", "1\n2.5\n-0.5\n10\n");
    CHECK_NEAR(sum_numbers_in_file("numbers.txt"), 13.0);
}

TEST("sum_numbers_in_file: skips lines that aren't one number") {
    grader::write_file("messy.txt", "10\nabc\n-2.5\n3 4\n\n  4  \n12 apples\n");
    CHECK_NEAR(sum_numbers_in_file("messy.txt"), 11.5);
}

TEST("sum_numbers_in_file: missing file throws") {
    CHECK_THROWS(std::runtime_error, sum_numbers_in_file("absent.txt"));
}
