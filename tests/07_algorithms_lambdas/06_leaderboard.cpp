#include "grader.hpp"
#include "07_algorithms_lambdas/06_leaderboard.cpp"

PROGRAM_TEST("One result per player", {
    .input = "alice 30\nbob 50\ncarol 10\n",
    .output = "1. bob 50\n2. alice 30\n3. carol 10\n",
});

PROGRAM_TEST("Points add up across lines", {
    .input = "alice 30\nbob 20\nalice 15\nbob 1\n",
    .output = "1. alice 45\n2. bob 21\n",
});

PROGRAM_TEST("Ties share a rank and sort by name", {
    .input = "dave 50\nalice 40\ncarol 20\nbob 10\ncarol 30\n",
    .output = "1. carol 50\n1. dave 50\n3. alice 40\n4. bob 10\n",
});

PROGRAM_TEST("Tie in the middle of the table", {
    .input = "a 30\nc 20\nb 20\nd 10\n",
    .output = "1. a 30\n2. b 20\n2. c 20\n4. d 10\n",
});

PROGRAM_TEST("Everyone tied", {
    .input = "zed 5\namy 5\nmo 5\n",
    .output = "1. amy 5\n1. mo 5\n1. zed 5\n",
});

PROGRAM_TEST("Negative points", {
    .input = "alice 10\nbob -5\nalice -20\n",
    .output = "1. bob -5\n2. alice -10\n",
});

PROGRAM_TEST("Blank and bad lines are skipped", {
    .input = "alice 10\n\nbogus\nbob x\nbob 5 extra\ncarol 7\n   \n",
    .output = "1. alice 10\n2. carol 7\n",
});

PROGRAM_TEST("No input, no output", {
    .input = "",
    .output = "",
});
