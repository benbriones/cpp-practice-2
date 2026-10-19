// Challenge: Leaderboard
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
// Grade: grade 07_algorithms_lambdas/06_leaderboard
// Try it: grade --run 07_algorithms_lambdas/06_leaderboard

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
