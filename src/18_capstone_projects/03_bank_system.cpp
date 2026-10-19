// Challenge: Bank system
// A command interpreter for a tiny bank. Read commands from standard input,
// one per line, and answer each one:
//
//     open alice 100                 →  opened alice with 100.00
//     deposit alice 50               →  alice: 150.00
//     withdraw alice 30              →  alice: 120.00
//     transfer alice bob 30          →  alice: 90.00, bob: 30.00
//     report                         →  alice          90.00
//                                       bob            30.00
//                                       total         120.00
//
// report lists every account sorted by name, then the total, each line
// formatted with std::format("{:<10}{:>10.2f}", name, dollars).
// An amount is digits, optionally followed by '.' and one or two digits
// ("12", "12.5", "12.50"). open accepts 0; every other command needs more than 0.
// Blank lines are ignored.
//
// When a command can't be carried out, print one of these, change nothing,
// and carry on with the next line:
//     error: unknown command 'close'
//     error: wrong number of arguments for 'deposit'
//     error: invalid amount '12.345'
//     error: account 'alice' already exists
//     error: no account 'carol'
//     error: cannot transfer to the same account
//     error: insufficient funds in 'alice'
// Check in that order: command, argument count, amount, accounts (the first
// named account first), funds.
//
// Suggested design: a Bank class whose methods throw (std::invalid_argument,
// std::runtime_error, ...), and a main loop that catches std::exception and
// prints "error: " + e.what(). Keep money as whole cents in a long long so
// 0.10 + 0.20 is exactly 0.30.
//
// ./grade 18_capstone_projects/03_bank_system
// Try it: grade --run 18_capstone_projects/03_bank_system

#include <format>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    throw "TODO";
}
