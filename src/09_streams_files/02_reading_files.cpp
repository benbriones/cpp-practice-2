// Exercise: Reading files
// std::ifstream in(path);  opens a file for reading (<fstream>). Then read it
// exactly like std::cin: std::getline(in, line), in >> word.
// Opening can fail (missing file, no permission), so check: if (!in) { ... }
//
// Every function throws std::runtime_error("can't open " + path) when the file
// can't be opened.
//
// Grade: grade 09_streams_files/02_reading_files

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
