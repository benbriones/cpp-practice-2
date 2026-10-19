// === Lesson: Reading input and printing output ===============================
//
// <iostream> provides std::cin (standard input) and std::cout (standard
// output). << sends values to a stream; >> reads values from one:
//
//     std::string name;
//     int age = 0;
//     std::cin >> name >> age;                       // input: Ada 36
//     std::cout << name << " is " << age << '\n';    // Ada is 36
//
// >> skips whitespace (spaces, tabs, newlines) and then reads one value, so
// "1 2", "1\n2" and "  1\n\n 2" all read as the same two numbers.
//
// The expression std::cin >> x also works as a condition: true if a value was
// read, false at the end of input or when the next text isn't a number. That's
// the standard way to read until the input runs out:
//
//     double price = 0;
//     int items = 0;
//     while (std::cin >> price) {
//         ++items;
//     }
//
// In a terminal, end the input with Ctrl-D. Bad input, like "abc" for an
// int, also ends the loop; module 09 covers recovering from it.
//
// '\n' ends a line. std::endl does the same and also flushes the stream,
// which is slower, so prefer '\n'.
//
// Formatting decimals: std::fixed means "plain decimal notation" and
// std::setprecision(n) then means "n digits after the point". Both come from
// <iomanip> and stay in effect for everything printed afterwards. Values are
// rounded, not cut off:
//
//     std::cout << std::fixed << std::setprecision(3);
//     std::cout << 2.0 << ' ' << 2.0 / 3;     // 2.000 0.667
//
// A running minimum or maximum that starts at 0 is wrong when every value is
// negative (or every value is positive). Start from the first value read, or
// from std::numeric_limits<int>::max() / lowest() in <limits>. std::min(a, b)
// and std::max(a, b) are in <algorithm>.
//
// Program exercises are graded by running main() with the test's input on
// stdin and comparing what it prints, line by line. main() returns 0 if it
// ends without a return statement.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/
//            https://www.learncpp.com/cpp-tutorial/output-with-ostream-and-ios/
//
// === Challenge: Number report ================================================
// Write a complete program. Read whole numbers from standard input until it
// runs out, then print a report in exactly this format:
//
//     count: 4
//     sum: 10
//     min: 1
//     max: 4
//     mean: 2.50
//
// The mean always has two decimal places. With no numbers at all, print only:
//     no numbers
//
// ./grade 01_basics/05_number_report
// Try it: ./grade --run 01_basics/05_number_report   (type numbers, then Ctrl-D)

#include <iostream>

int main() {
    throw "TODO";
}
