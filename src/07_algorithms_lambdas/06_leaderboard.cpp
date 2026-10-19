// === Lesson: Strict line parsing, and sorting a map's contents ===============
//
// Command-line tools usually read standard input a line at a time, then parse
// each line on its own. That way one bad line can't knock the rest out of step:
//
//     std::string line;
//     while (std::getline(std::cin, line)) {     // false at end of input
//         ...
//     }
//
// A std::istringstream reads words and numbers out of one line with >>, skipping
// spaces. Each >> leaves the stream in a failed state when it can't read what you
// asked for, and the stream converts to false. Being strict means checking that
// the reads worked *and* that nothing is left over:
//
//     // Accepts exactly two whole numbers, like "3 -4".
//     bool parse_point(const std::string& line, int& x, int& y) {
//         std::istringstream in(line);
//         std::string extra;
//         return (in >> x >> y) && !(in >> extra);
//     }
//
// The leftover check matters because >> stops at the first character that can't
// be part of the number: reading an int from "4x" or "4.5" succeeds with 4 and
// leaves "x" or ".5" behind.
//
// Errors go to std::cerr, a separate stream from std::cout. A user sees both in
// the terminal, but a pipe or a grader reading std::cout sees only the output.
//
// A std::map keeps its keys sorted, but only by key. To order entries by value,
// copy them into a vector of pairs; a vector can be built from any iterator range:
//
//     std::map<std::string, double> temps{{"oslo", 4.5}, {"lima", 19.0}};
//     std::vector<std::pair<std::string, double>> rows(temps.begin(), temps.end());
//     std::sort(rows.begin(), rows.end(), [](const auto& a, const auto& b) {
//         return a.second > b.second;                  // warmest first
//     });
//     for (const auto& [city, temp] : rows) std::cout << city << ' ' << temp << '\n';
//
// A lambda parameter declared `const auto&` takes whatever type it's given,
// which saves spelling out std::pair<std::string, double>.
//
// To try a program by hand, type the input and end it with Ctrl-D, or redirect a
// file into it: ./grade --run <exercise> < input.txt
//
// Read more: https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/
//            https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
//
// === Challenge: Leaderboard ==================================================
// Read game results from standard input, one per line: a player name and the
// points they scored, e.g. "alice 30". Points are whole numbers and may be
// negative; a player can appear on many lines. Print every player's total,
// highest first, with equal totals in alphabetical order. Tied players share a
// rank, and the next rank skips ahead:
//
//     1. carol 50
//     1. dave 50
//     3. alice 40
//     4. bob 10
//
// Skip blank lines. Any other line that isn't exactly "<name> <points>" is bad:
// print "skipping bad line: <the line>" to std::cerr and carry on. No valid lines
// means no output at all.
//
// Hint: total the points in a std::map<std::string, int>, then copy the entries
// into a std::vector of pairs and sort it with a lambda.
//
// ./grade 07_algorithms_lambdas/06_leaderboard
// Try it: ./grade --run 07_algorithms_lambdas/06_leaderboard

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main() {
    throw "TODO";
}
