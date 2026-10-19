// === Lesson: Writing files ===================================================
//
// std::ofstream (<fstream>) opens a file for writing; then you write with <<,
// as with std::cout. The open mode decides what happens to an existing file:
//
//     std::ofstream out(path);                     // create, or empty an existing file
//     std::ofstream log(path, std::ios::app);      // create, or append at the end
//     std::ofstream raw(path, std::ios::binary);   // bytes exactly as given
//     std::ofstream both(path, std::ios::app | std::ios::binary);   // modes combine
//
// The file is created (or emptied) the moment the stream is constructed, before
// you write a single character. So if you only want a file under some
// condition, check that condition before constructing the stream.
//
// Opening fails, without an exception, when the folder doesn't exist or you
// lack permission. Check with if (!out), just like an input stream:
//
//     std::ofstream out("scores.csv");
//     if (!out) {
//         throw std::runtime_error("can't write scores.csv");
//     }
//     out << "name,points\n";
//     for (const auto& [name, points] : table) {   // a map<string, int>
//         out << std::format("{},{}\n", name, points);
//     }
//
// Writes are buffered and reach the disk when the stream is flushed, which
// happens at the latest when it closes at the end of its scope. Prefer '\n'
// to std::endl: endl also flushes, which is slow inside a loop.
//
// Text vs. binary. On Windows, text mode turns '\n' into "\r\n" on the way
// out (and back on the way in); std::ios::binary switches that off. macOS and
// Linux never translate, but open in binary mode whenever bytes must survive
// unchanged, so the code is right everywhere.
//
// Handy for tables: std::string(5, '*') is "*****", and the std::format
// alignment specs from the last exercise ({:<10}, {:>8}) work in files too.
//
// Read more: https://www.learncpp.com/cpp-tutorial/basic-file-io/
//
// === Exercise: Writing files =================================================
// Implement the four functions below.
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
