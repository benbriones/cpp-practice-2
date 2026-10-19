#include "grader.hpp"
#include "01_basics/05_number_report.cpp"

PROGRAM_TEST("Four numbers on one line", {
    .input = "1 2 3 4\n",
    .output = "count: 4\nsum: 10\nmin: 1\nmax: 4\nmean: 2.50\n",
});

PROGRAM_TEST("Numbers spread over several lines", {
    .input = "10\n  20\n\n30\n",
    .output = "count: 3\nsum: 60\nmin: 10\nmax: 30\nmean: 20.00\n",
});

PROGRAM_TEST("A single number", {
    .input = "7\n",
    .output = "count: 1\nsum: 7\nmin: 7\nmax: 7\nmean: 7.00\n",
});

PROGRAM_TEST("Negative numbers", {
    .input = "-5 -1 -9\n",
    .output = "count: 3\nsum: -15\nmin: -9\nmax: -1\nmean: -5.00\n",
});

PROGRAM_TEST("Mean is rounded to two places", {
    .input = "1 1 2\n",
    .output = "count: 3\nsum: 4\nmin: 1\nmax: 2\nmean: 1.33\n",
});

PROGRAM_TEST("No input at all", {
    .input = "",
    .output = "no numbers\n",
});
