#include "grader.hpp"
#include "04_structs_enums/04_inventory.cpp"

PROGRAM_TEST("Add items and list them", {
    .input = "add apple 5\nadd pear 2\nlist\n",
    .output = "apple: 5\npear: 2\n",
});

PROGRAM_TEST("Count items, including unknown ones", {
    .input = "add apple 5\ncount apple\ncount kiwi\n",
    .output = "apple: 5\nkiwi: 0\n",
});

PROGRAM_TEST("Adding to an existing item keeps its place", {
    .input = "add apple 1\nadd pear 1\nadd apple 2\nlist\n",
    .output = "apple: 3\npear: 1\n",
});

PROGRAM_TEST("Remove some units", {
    .input = "add apple 5\nremove apple 2\ncount apple\n",
    .output = "apple: 3\n",
});

PROGRAM_TEST("An item that reaches zero leaves the list", {
    .input = "add apple 2\nadd pear 1\nremove apple 2\nlist\ncount apple\nadd apple 4\nlist\n",
    .output = "pear: 1\napple: 0\npear: 1\napple: 4\n",
});

PROGRAM_TEST("Removing too much or something missing", {
    .input = "add apple 3\nremove apple 5\nremove pear 1\nlist\n",
    .output = "error: only 3 apple in stock\nerror: no pear in stock\napple: 3\n",
});

PROGRAM_TEST("Bad quantities", {
    .input = "add apple x\nadd apple 0\nadd apple -2\nadd apple 1.5\n"
             "add apple\nremove apple two\nlist\n",
    .output = "error: bad quantity 'x'\nerror: bad quantity '0'\nerror: bad quantity '-2'\n"
              "error: bad quantity '1.5'\nerror: bad quantity ''\n"
              "error: bad quantity 'two'\n(empty)\n",
});

PROGRAM_TEST("Unknown commands and blank lines", {
    .input = "\nsell apple 2\n\nadd apple 1\nhelp\nlist\n",
    .output = "error: unknown command 'sell'\nerror: unknown command 'help'\napple: 1\n",
});

PROGRAM_TEST("Empty list", {
    .input = "list\n",
    .output = "(empty)\n",
});

PROGRAM_TEST("No input at all", {
    .input = "",
    .output = "",
});
