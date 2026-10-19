#include "grader.hpp"
#include "18_capstone_projects/03_bank_system.cpp"

PROGRAM_TEST("open and report", {
    .input = "open alice 100\n"
             "open bob 20.5\n"
             "report\n",
    .output = "opened alice with 100.00\n"
              "opened bob with 20.50\n"
              "alice         100.00\n"
              "bob            20.50\n"
              "total         120.50\n",
});

PROGRAM_TEST("deposit and withdraw", {
    .input = "open alice 100\n"
             "deposit alice 50.25\n"
             "withdraw alice 149.25\n",
    .output = "opened alice with 100.00\n"
              "alice: 150.25\n"
              "alice: 1.00\n",
});

PROGRAM_TEST("transfer", {
    .input = "open alice 120\n"
             "open bob 0\n"
             "transfer alice bob 30\n"
             "report\n",
    .output = "opened alice with 120.00\n"
              "opened bob with 0.00\n"
              "alice: 90.00, bob: 30.00\n"
              "alice          90.00\n"
              "bob            30.00\n"
              "total         120.00\n",
});

PROGRAM_TEST("report is sorted by name", {
    .input = "open zed 5\n"
             "open amy 1.10\n"
             "report\n",
    .output = "opened zed with 5.00\n"
              "opened amy with 1.10\n"
              "amy             1.10\n"
              "zed             5.00\n"
              "total           6.10\n",
});

PROGRAM_TEST("report with no accounts", {
    .input = "report\n",
    .output = "total           0.00\n",
});

PROGRAM_TEST("cents add up exactly", {
    .input = "open alice 0\n"
             "deposit alice 0.10\n"
             "deposit alice 0.20\n"
             "withdraw alice 0.30\n",
    .output = "opened alice with 0.00\n"
              "alice: 0.10\n"
              "alice: 0.30\n"
              "alice: 0.00\n",
});

PROGRAM_TEST("unknown commands and wrong argument counts", {
    .input = "close alice\n"
             "open alice\n"
             "open alice 10 extra\n"
             "report now\n"
             "transfer alice 5\n",
    .output = "error: unknown command 'close'\n"
              "error: wrong number of arguments for 'open'\n"
              "error: wrong number of arguments for 'open'\n"
              "error: wrong number of arguments for 'report'\n"
              "error: wrong number of arguments for 'transfer'\n",
});

PROGRAM_TEST("invalid amounts", {
    .input = "open alice 12x\n"
             "open alice -5\n"
             "open alice 1.234\n"
             "open alice .5\n"
             "open alice 10\n"
             "deposit alice 0\n"
             "withdraw alice 3.\n",
    .output = "error: invalid amount '12x'\n"
              "error: invalid amount '-5'\n"
              "error: invalid amount '1.234'\n"
              "error: invalid amount '.5'\n"
              "opened alice with 10.00\n"
              "error: invalid amount '0'\n"
              "error: invalid amount '3.'\n",
});

PROGRAM_TEST("account errors leave balances unchanged", {
    .input = "open alice 50\n"
             "open alice 10\n"
             "deposit carol 5\n"
             "withdraw alice 60\n"
             "transfer alice alice 5\n"
             "transfer carol alice 5\n"
             "transfer alice dave 5\n"
             "transfer alice dave abc\n"
             "report\n",
    .output = "opened alice with 50.00\n"
              "error: account 'alice' already exists\n"
              "error: no account 'carol'\n"
              "error: insufficient funds in 'alice'\n"
              "error: cannot transfer to the same account\n"
              "error: no account 'carol'\n"
              "error: no account 'dave'\n"
              "error: invalid amount 'abc'\n"
              "alice          50.00\n"
              "total          50.00\n",
});

PROGRAM_TEST("blank lines are ignored", {
    .input = "\n"
             "open alice 5\n"
             "\n"
             "   \n"
             "deposit alice 5\n",
    .output = "opened alice with 5.00\n"
              "alice: 10.00\n",
});

PROGRAM_TEST("no input, no output", {
    .input = "",
    .output = "",
});
