// === Lesson: String streams and std::format ==================================
//
// A stream is a source or destination of text. std::cin, files and strings all
// use the same operators, so code written for one works for the others:
//
//     std::istringstream in("3 1.5 kiwi");    // read from a string (<sstream>)
//     int count;  double weight;  std::string fruit;
//     in >> count >> weight >> fruit;         // >> skips whitespace, then parses
//
//     std::ostringstream out;                 // write into a string
//     out << "x=" << 3 << ", y=" << 4.5;
//     std::string text = out.str();           // "x=3, y=4.5"
//
// The result of `in >> x` is the stream, which converts to bool: true while
// reads succeed. That makes "read until it stops working" a one-line loop:
//
//     double total = 0, x;
//     while (in >> x) total += x;             // stops at end of input or bad text
//
// Stream state. A read that can't parse sets the fail flag, stores 0, and
// leaves the offending characters unread. From then on every read fails
// immediately, until in.clear() resets the flags:
//
//     std::istringstream in("42 abc");
//     int n;
//     in >> n;        // ok: n == 42
//     in >> n;        // fails: "abc" isn't an int; n == 0, in.fail() is true
//     in >> n;        // fails without even looking
//     in.clear();     // flags reset, but "abc" is still the next thing to read
//
// std::format (C++20, <format>) fills a pattern, like Python's str.format.
// Each {} takes the next argument; after a colon comes a spec:
// [align][width][.precision][type], with < left, > right, ^ middle:
//
//     std::format("{:<6}|{:>5}|{:^7}|", "ab", 42, "mid")   // "ab    |   42|  mid  |"
//     std::format("{:.3f} {:>8.1f}", 3.14159, 9.87)        // "3.142      9.9"
//     std::format("{:>{}}", "hi", 6)                       // "    hi"
//
// A width is a minimum: longer values are never cut. A nested {} takes the
// width (or the precision) from the next argument, as in the last line.
// Older code uses <iomanip> instead:
// out << std::fixed << std::setprecision(2) << 3.14159 writes "3.14".
//
// Read more: https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/
//            https://en.cppreference.com/w/cpp/utility/format/spec
//
// === Exercise: String streams and formatting =================================
// Implement the four functions below.
//
// ./grade 09_streams_files/01_string_streams

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
