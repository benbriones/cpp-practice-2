// Challenge: Word count
// Write a program that reads text from standard input and prints:
//
//     lines: 3
//     words: 9
//     longest: elephant
//
// Words are runs of non-whitespace characters, punctuation included. If two
// words tie for longest, report the first. With no words, print
// "longest: (none)". A last line without a trailing newline still counts.
//
// Hint: std::getline(std::cin, line) reads one line. To pull words out of a
// line: std::istringstream words(line); while (words >> word) { ... }  (<sstream>)
//
// ./grade 02_strings_vectors/05_word_count
// Try it: grade --run 02_strings_vectors/05_word_count < some_file.txt

#include <iostream>
#include <sstream>
#include <string>

int main() {
    throw "TODO";
}
