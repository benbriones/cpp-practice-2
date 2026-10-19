// Challenge: CSV salary report
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
// Hint: std::getline(line_stream, field, ',') splits on commas.
//
// Grade: grade 09_streams_files/04_csv_report
// Try it: grade --run 09_streams_files/04_csv_report < salaries.csv

#include <format>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {
    throw "TODO";
}
