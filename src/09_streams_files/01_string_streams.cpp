// Exercise: String streams and formatting
// Streams read and write text the same way whether the other end is the
// console, a file, or a string. Implement the four functions below.
//
// std::istringstream in(text); in >> x;  reads from a string just like std::cin.
// A failed read puts the stream into a fail state: `if (in >> x)` is false, and
// every later read fails too until you call in.clear().
// std::format("{:<8}{:>6.2f}", name, price) left-aligns name in 8 columns, then
// right-aligns price in 6 columns with 2 decimals (<format>).
//
// Grade: grade 09_streams_files/01_string_streams

#include <format>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

// The whitespace-separated integers at the start of text, stopping at the first
// token that isn't an integer: parse_ints("4 8 x 15") == {4, 8}.
std::vector<int> parse_ints(const std::string& text) {
    throw "TODO";
}

// Every integer in `in` up to the end of input, skipping tokens that aren't
// integers: "1 two 3" gives {1, 3}.
// Hint: after a failed read, clear() the stream, then read the bad token into a
// std::string to get past it.
std::vector<int> read_valid_ints(std::istream& in) {
    throw "TODO";
}

// One table row: name left-aligned in 12 columns, quantity right-aligned in 5,
// price right-aligned in 10 with 2 decimals. Long names are not cut off.
// format_row("Widget", 3, 4.5) == "Widget          3      4.50"
std::string format_row(const std::string& name, int quantity, double price) {
    throw "TODO";
}

// value with exactly `decimals` digits after the point (0 means no point):
// to_fixed(3.14159, 2) == "3.14", to_fixed(2, 3) == "2.000", to_fixed(2.7, 0) == "3"
std::string to_fixed(double value, int decimals) {
    throw "TODO";
}
