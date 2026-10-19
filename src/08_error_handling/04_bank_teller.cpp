// Challenge: Bank teller
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
// Hint: std::stoi(text, &used) also reports how many characters it used.
//
// ./grade 08_error_handling/04_bank_teller
// Try it: grade --run 08_error_handling/04_bank_teller

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
