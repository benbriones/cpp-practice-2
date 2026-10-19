#include "grader.hpp"
#include "09_streams_files/03_writing_files.cpp"

TEST("write_lines: one line per element") {
    write_lines("out.txt", {"alpha", "beta", "gamma"});
    CHECK_EQ(grader::read_file("out.txt"), "alpha\nbeta\ngamma\n");
}

TEST("write_lines: replaces existing content") {
    grader::write_file("out.txt", "old content that should disappear\n");
    write_lines("out.txt", {"new"});
    CHECK_EQ(grader::read_file("out.txt"), "new\n");
}

TEST("write_lines: no lines makes an empty file") {
    write_lines("empty.txt", {});
    CHECK(std::filesystem::exists("empty.txt"), "write_lines should create the file");
    CHECK_EQ(grader::read_file("empty.txt"), "");
}

TEST("write_lines: unwritable path throws") {
    CHECK_THROWS(std::runtime_error, write_lines("no_such_folder/out.txt", {"x"}));
}

TEST("append_line: creates the file, then appends") {
    append_line("log.txt", "started");
    append_line("log.txt", "working");
    append_line("log.txt", "done");
    CHECK_EQ(grader::read_file("log.txt"), "started\nworking\ndone\n");
}

TEST("append_line: keeps existing content") {
    grader::write_file("log.txt", "line 1\n");
    append_line("log.txt", "line 2");
    CHECK_EQ(grader::read_file("log.txt"), "line 1\nline 2\n");
}

TEST("write_report: layout and total") {
    write_report("report.txt", {{"alice", 42}, {"bob", 7}});
    CHECK_EQ(grader::read_file("report.txt"),
             "name        points\n"
             "alice           42\n"
             "bob              7\n"
             "------------------\n"
             "total           49\n");
}

TEST("write_report: no scores") {
    write_report("report.txt", {});
    CHECK_EQ(grader::read_file("report.txt"),
             "name        points\n"
             "------------------\n"
             "total            0\n");
}

TEST("write_report: unwritable path throws") {
    CHECK_THROWS(std::runtime_error, write_report("missing_dir/report.txt", {{"a", 1}}));
}

TEST("copy_file: copies text exactly") {
    grader::write_file("source.txt", "first line\nsecond line, no newline");
    CHECK_EQ(copy_file("source.txt", "copy.txt"), true);
    CHECK_EQ(grader::read_file("copy.txt"), "first line\nsecond line, no newline");
}

TEST("copy_file: copies binary data, including zero bytes") {
    const std::string bytes("\x01\x00\xff\n\r\x00z", 7);
    grader::write_file("data.bin", bytes);
    CHECK_EQ(copy_file("data.bin", "data_copy.bin"), true);
    CHECK_EQ(grader::read_file("data_copy.bin"), bytes);
}

TEST("copy_file: missing source returns false and creates nothing") {
    CHECK_EQ(copy_file("ghost.txt", "should_not_exist.txt"), false);
    CHECK(!std::filesystem::exists("should_not_exist.txt"), "copy_file shouldn't create dst");
}
