// === Lesson: Reading lines and words =========================================
//
// std::cin >> word reads one whitespace-separated word, so it can't tell where
// lines end. To work line by line, use std::getline from <string>:
//
//     std::string line;
//     while (std::getline(std::cin, line)) {    // false once input runs out
//         ...                                   // line has no trailing '\n'
//     }
//
// getline reads up to the next '\n' and drops it. An empty line comes back as
// "", and a last line with no '\n' after it is still returned. Like >>, the
// call itself is the loop condition. This numbers the non-empty lines:
//
//     std::string line;
//     int number = 0;
//     while (std::getline(std::cin, line)) {
//         if (line.empty()) {
//             continue;
//         }
//         ++number;
//         std::cout << number << ": " << line << '\n';
//     }
//
// To read words or numbers out of a string you already have, wrap it in a
// std::istringstream (from <sstream>). It's an input stream like std::cin that
// reads from the string:
//
//     std::istringstream in("3 4   5");
//     int x = 0;
//     int total = 0;
//     while (in >> x) {
//         total += x;           // total ends up 12
//     }
//
// Mixing >> and getline on one stream is a classic trap: after std::cin >> n
// reads a number, the rest of that line (often just '\n') is still waiting, so
// the next getline returns "". Stick to one style per input.
//
// Keeping a "best so far": comparing with > keeps the first of several equal
// values, while >= keeps the last.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/
//            https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/
//
// === Challenge: Word count ===================================================
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
// ./grade 02_strings_vectors/05_word_count
// Try it: ./grade --run 02_strings_vectors/05_word_count < some_file.txt

#include <iostream>
#include <sstream>
#include <string>

int main() {
    throw "TODO";
}
