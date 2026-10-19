#include "grader.hpp"
#include "08_error_handling/04_bank_teller.cpp"

PROGRAM_TEST("Deposits, withdrawals, balance", {
    .input = "deposit 100\nwithdraw 30\nbalance\n",
    .output = "balance: 100\nbalance: 70\nbalance: 70\nfinal balance: 70\n",
});

PROGRAM_TEST("No commands at all", {
    .input = "",
    .output = "final balance: 0\n",
});

PROGRAM_TEST("Insufficient funds leaves the balance alone", {
    .input = "deposit 50\nwithdraw 80\nwithdraw 50\n",
    .output = "balance: 50\nerror: insufficient funds (balance: 50)\nbalance: 0\nfinal balance: 0\n",
});

PROGRAM_TEST("Amounts must be positive", {
    .input = "deposit -5\nwithdraw 0\ndeposit 0\n",
    .output = "error: amount must be positive\nerror: amount must be positive\n"
              "error: amount must be positive\nfinal balance: 0\n",
});

PROGRAM_TEST("Invalid and missing amounts", {
    .input = "deposit abc\ndeposit 5.5\nwithdraw 5x\ndeposit\nwithdraw\n",
    .output = "error: invalid amount 'abc'\nerror: invalid amount '5.5'\nerror: invalid amount '5x'\n"
              "error: missing amount\nerror: missing amount\nfinal balance: 0\n",
});

PROGRAM_TEST("Unknown commands", {
    .input = "transfer 5\nDEPOSIT 5\n",
    .output = "error: unknown command 'transfer'\nerror: unknown command 'DEPOSIT'\nfinal balance: 0\n",
});

PROGRAM_TEST("Keeps going after errors, skips blank lines", {
    .input = "deposit 20\n\nwithdraw 100\nfly\n\ndeposit 5\nbalance\n",
    .output = "balance: 20\nerror: insufficient funds (balance: 20)\nerror: unknown command 'fly'\n"
              "balance: 25\nbalance: 25\nfinal balance: 25\n",
});
