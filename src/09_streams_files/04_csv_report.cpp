// === Lesson: Parsing delimited text ==========================================
//
// A program that processes input usually reads standard input line by line
// until it runs out. std::getline returns false at end of input (end of the
// piped file, or Ctrl-D when you type into a terminal):
//
//     std::string line;
//     while (std::getline(std::cin, line)) {
//         // handle one line
//     }
//
// Splitting on a delimiter. std::getline takes an optional third argument, the
// character to stop at instead of '\n'. Run it on an istringstream over one
// line and each call hands you the next field:
//
//     std::istringstream parts("2024-03-15");
//     std::string piece;
//     std::vector<std::string> pieces;
//     while (std::getline(parts, piece, '-')) {
//         pieces.push_back(piece);              // "2024", "03", "15"
//     }
//
// Text to numbers. std::stoi and std::stod (<string>) convert a string and
// throw std::invalid_argument when there's no number at the start (and
// std::out_of_range when it's too big). But they stop quietly at the first
// character that doesn't fit:
//
//     std::stod("12.5")     // 12.5
//     std::stod("abc")      // throws std::invalid_argument
//     std::stod("7 days")   // 7: the rest is ignored
//
// To insist that the whole field is a number, pass a std::size_t* as the second
// argument: stod stores how many characters it used, and you compare that with
// the field's size(). Reading with >> from an istringstream works too.
//
// Two output streams. std::cout is the program's real output, the part another
// program or a test reads. std::cerr is for diagnostics: warnings and errors.
// Keeping them separate means `prog < in.csv > out.txt` still shows warnings on
// screen, and the tests here compare only std::cout.
//
// Grouping. A std::map keyed by name keeps its keys sorted, so iterating it
// gives a report in alphabetical order for free. Its value can be a small
// struct holding the running totals for that key.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/
//            https://en.cppreference.com/w/cpp/string/basic_string/stof
//
// === Challenge: CSV salary report ============================================
// Write a program that reads CSV from standard input and prints a summary per
// department. The first line is a header; skip it. Every other line is
// name,department,salary with no spaces around the commas, for example:
//
//     name,department,salary
//     Ada,Engineering,120000
//     Grace,Engineering,110000.50
//     Linus,Ops,90000
//
// Output, departments in alphabetical order:
//
//     department     count       total     average
//     Engineering        2   230000.50   115000.25
//     Ops                1    90000.00    90000.00
//
// Column widths: department left-aligned in 14, count right-aligned in 6, total
// and average right-aligned in 12 with 2 decimals. The header uses the same
// widths. Skip blank lines silently. A line without exactly three fields, or
// whose salary isn't a number, is skipped with a warning on std::cerr:
//     skipping line 4: Bob,Ops
// (line numbers count the header as line 1). If no valid rows remain, print
// only:  no data
//
// ./grade 09_streams_files/04_csv_report
// Try it: ./grade --run 09_streams_files/04_csv_report < salaries.csv

#include <format>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {
    throw "TODO";
}
