// Exercise: Writing files
// std::ofstream out(path);               creates the file, or empties an existing one
// std::ofstream out(path, std::ios::app); keeps the content and writes at the end
// Write with << just like std::cout. The file is flushed and closed when `out`
// goes out of scope.
//
// ./grade 09_streams_files/03_writing_files

#include <format>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

// Write each line followed by '\n', replacing any existing content.
// Throws std::runtime_error("can't write " + path) if the file can't be opened.
void write_lines(const std::string& path, const std::vector<std::string>& lines) {
    throw "TODO";
}

// Add text plus '\n' to the end of the file, creating the file if needed.
void append_line(const std::string& path, const std::string& text) {
    throw "TODO";
}

struct Score {
    std::string name;
    int points = 0;
};

// Write a report: names left-aligned in 10 columns, numbers right-aligned in 8.
//
//     name        points
//     alice           42
//     bob              7
//     ------------------
//     total           49
//
// The dashed line is 18 '-' characters. Every line ends with '\n'.
// Throws std::runtime_error("can't write " + path) if the file can't be opened.
void write_report(const std::string& path, const std::vector<Score>& scores) {
    throw "TODO";
}

// Copy src to dst byte for byte, and return true. If src can't be opened,
// return false without creating dst.
// Hint: open both with std::ios::binary; `out << in.rdbuf();` copies everything.
bool copy_file(const std::string& src, const std::string& dst) {
    throw "TODO";
}
