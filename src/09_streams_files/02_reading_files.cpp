// === Lesson: Reading files ===================================================
//
// std::ifstream (<fstream>) opens a file for reading. After that it's an
// ordinary input stream, so >> and std::getline work exactly as with std::cin.
// A relative path is relative to the directory the program runs in.
//
// Opening can fail (missing file, no permission) without any exception: the
// stream just starts out failed. Check it before reading:
//
//     std::ifstream in("todo.txt");
//     if (!in) {
//         throw std::runtime_error("can't open todo.txt");   // <stdexcept>
//     }
//
// You never close it by hand: the file closes when `in` goes out of scope.
//
// Line by line. std::getline(in, line) reads up to the next '\n', drops the
// '\n', and returns the stream, so it fits a while condition. A last line
// with no '\n' after it is still read; at end of input the loop simply stops:
//
//     std::string line;
//     int number = 0;
//     while (std::getline(in, line)) {
//         std::cout << ++number << ": " << line << '\n';
//     }
//
// Avoid `while (!in.eof()) { getline(...); ... }`. eof() turns true only once
// a read runs into the end of the file, so after a final '\n' that loop goes
// round once more and handles an extra, empty "line".
//
// Word by word. in >> word skips any whitespace, newlines included, and reads
// up to the next whitespace. It knows nothing about lines.
//
// Mixing the two trips people up: after in >> n, the '\n' that ended the number
// is still unread, so the next getline returns an empty string.
//
// Parsing inside a line. Wrap the line in its own std::istringstream and use
// >> on that; a failure then affects only this line, not the file stream.
// The manipulator std::ws skips whitespace: `stream >> std::ws` moves past any
// spaces, tabs and newlines without reading anything else.
//
//     std::istringstream fields("  7 kg");
//     int amount;  std::string unit;
//     fields >> amount >> unit;               // 7 and "kg"
//
// Read more: https://www.learncpp.com/cpp-tutorial/basic-file-io/
//            https://www.learncpp.com/cpp-tutorial/stream-states-and-input-validation/
//
// === Exercise: Reading files =================================================
// Every function throws std::runtime_error("can't open " + path) when the file
// can't be opened.
//
// ./grade 09_streams_files/02_reading_files

#include <cstddef>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Number of lines: "a\nb\n" has 2, a last line without '\n' still counts, and
// an empty file has 0.
std::size_t count_lines(const std::string& path) {
    throw "TODO";
}

// Every line, without its newline.
std::vector<std::string> read_lines(const std::string& path) {
    throw "TODO";
}

// How often each whitespace-separated word appears, exactly as written
// (case-sensitive, punctuation included).
std::map<std::string, int> word_counts_in_file(const std::string& path) {
    throw "TODO";
}

// Sum of a file with one number per line. Lines that aren't exactly one number
// (surrounding spaces are fine) are skipped: "10\nabc\n-2.5\n3 4\n" sums to 7.5.
// Hint: per line, read a double from an istringstream, then check that only
// whitespace is left: (line_stream >> std::ws).eof()
double sum_numbers_in_file(const std::string& path) {
    throw "TODO";
}
