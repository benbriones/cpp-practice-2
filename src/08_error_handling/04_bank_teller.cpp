// === Lesson: Exceptions across a whole program ===============================
//
// In a real program, errors are detected deep inside and reported at the edge.
// A clean split:
//
//   classes and helpers   enforce their rules and throw when one is broken.
//   main()                reads input, calls them, catches, and tells the user.
//
// The class doesn't know how errors are shown, and main() doesn't know the rules.
//
// Check, then change. Validate everything before you modify any state, so a
// function that throws leaves the object exactly as it was. If a ticket counter
// subtracts first and checks afterwards, a failed sale has already lost tickets.
//
// One try per line of input. Catching inside the read loop turns an error into
// one message and the program carries on with the next line:
//
//     std::string line;
//     while (std::getline(std::cin, line)) {
//         try {
//             handle(line);                         // may throw from deep inside
//         } catch (const std::exception& e) {       // every standard exception
//             std::cout << "problem: " << e.what() << '\n';
//         }
//     }
//
// Translate low-level errors. std::stoi's own messages are terse library text
// ("stoi: no conversion" with libc++), not something to show a user. Catch them
// close to where they happen and throw your own exception with a useful message:
//
//     int parse_port(const std::string& text) {
//         try {
//             return std::stoi(text);
//         } catch (const std::exception&) {
//             throw std::invalid_argument("not a port number: '" + text + "'");
//         }
//     }
//
// std::stoi(text, &used) also stores in `used` (a std::size_t) how many characters
// it consumed, so used != text.size() tells you there was trailing junk.
//
// Read more: https://www.learncpp.com/cpp-tutorial/exceptions-functions-and-stack-unwinding/
//            https://www.learncpp.com/cpp-tutorial/rethrowing-exceptions/
//
// === Challenge: Bank teller ==================================================
// A program that runs one bank account (starting at 0) from commands on standard
// input, one per line. Amounts are whole numbers.
//
//     deposit 100      → balance: 100
//     withdraw 30      → balance: 70
//     balance          → balance: 70
//
// Every problem prints one error line and the program carries on:
//
//     withdraw 500     → error: insufficient funds (balance: 70)
//     deposit -5       → error: amount must be positive      (also for 0)
//     deposit abc      → error: invalid amount 'abc'          (also "5.5", "5x")
//     deposit          → error: missing amount
//     transfer 5       → error: unknown command 'transfer'
//
// Skip blank lines. After the last line, print "final balance: <balance>".
//
// Design: put the rules in Account; deposit and withdraw throw (std::invalid_argument,
// std::runtime_error) with the text after "error: " as the message. main() reads
// lines, catches const std::exception&, and prints "error: " + e.what().
//
// ./grade 08_error_handling/04_bank_teller
// Try it: ./grade --run 08_error_handling/04_bank_teller

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class Account {
public:
    void deposit(int amount) {
        throw "TODO";
    }

    void withdraw(int amount) {
        throw "TODO";
    }

    int balance() const {
        throw "TODO";
    }

private:
    // TODO: the data member(s) you need
};

int main() {
    throw "TODO";
}
