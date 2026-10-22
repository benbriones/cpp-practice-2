// === Lesson: Command interpreters ============================================
//
// A program that reads commands is easiest to get right in three layers:
//
//     input loop   read a line, split it into words, skip blank lines
//     dispatch     check the command name and argument count, convert the
//                  arguments from text, then call the model
//     model        the domain itself (here, the bank): plain methods on plain
//                  data that know nothing about text, and throw on bad requests
//
// Errors as exceptions. When the model throws, the loop catches, prints, and
// goes on to the next line. Every standard exception carries its message in
// what(), so one handler covers them all:
//
//     try {
//         library.lend(title, member);              // throws on any problem
//     } catch (const std::exception &e) {
//         std::cout << "error: " << e.what() << '\n';
//     }
//
// Validate, then change. A request that fails must leave everything as it was,
// so make every check before the first change:
//
//     void Library::rename(const std::string &from, const std::string &to) {
//         if (!books_.contains(from)) throw std::runtime_error("no " + from);
//         if (books_.contains(to)) throw std::runtime_error(to + " exists");
//         books_[to] = books_[from];   // every check passed; now change things
//         books_.erase(from);
//     }
//
// Money in cents. A double can't hold 0.10 exactly, so totals drift and
// conversions surprise you: static_cast<long long>(0.29 * 100) is 28. Store
// whole cents in an integer, and turn text like "12.5" into 1250 yourself,
// from the digits before and after the '.'. Use a double only for printing.
//
// std::format aligns columns: in "{:<8}|{:>8.2f}", <8 pads on the right to
// width 8, >8 pads on the left, and .2f prints two decimals:
//
//     std::format("{:<8}|{:>8.2f}", "tea", 3.5)   →   "tea     |    3.50"
//
// Read more: https://en.cppreference.com/w/cpp/utility/format/spec
//
// === Challenge: Bank system ==================================================
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
// prints "error: " + e.what(). Keep money as whole cents in a long long.
//
// ./grade 18_capstone_projects/03_bank_system
// Try it: ./grade --run 18_capstone_projects/03_bank_system

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
