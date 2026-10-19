#include "grader.hpp"
#include "09_streams_files/04_csv_report.cpp"

PROGRAM_TEST("Two departments", {
    .input = "name,department,salary\n"
             "Ada,Engineering,120000\n"
             "Grace,Engineering,110000.50\n"
             "Linus,Ops,90000\n",
    .output = "department     count       total     average\n"
              "Engineering        2   230000.50   115000.25\n"
              "Ops                1    90000.00    90000.00\n",
});

PROGRAM_TEST("Departments are sorted alphabetically", {
    .input = "name,department,salary\n"
             "Zed,Sales,50000\n"
             "Amy,Design,70000\n"
             "Max,Sales,70000\n"
             "Kim,Accounting,65000\n",
    .output = "department     count       total     average\n"
              "Accounting         1    65000.00    65000.00\n"
              "Design             1    70000.00    70000.00\n"
              "Sales              2   120000.00    60000.00\n",
});

PROGRAM_TEST("Malformed lines and blank lines are skipped", {
    .input = "name,department,salary\n"
             "Ada,Engineering,100\n"
             "\n"
             "Bob,Ops\n"
             "Cy,Ops,lots\n"
             "Di,Ops,1,2\n"
             "Ed,Ops,300\n",
    .output = "department     count       total     average\n"
              "Engineering        1      100.00      100.00\n"
              "Ops                1      300.00      300.00\n",
});

PROGRAM_TEST("Average keeps the fraction", {
    .input = "name,department,salary\n"
             "A,Team,1\n"
             "B,Team,2\n"
             "C,Team,2\n",
    .output = "department     count       total     average\n"
              "Team               3        5.00        1.67\n",
});

PROGRAM_TEST("Header only", {
    .input = "name,department,salary\n",
    .output = "no data\n",
});

PROGRAM_TEST("Empty input", {
    .input = "",
    .output = "no data\n",
});

PROGRAM_TEST("Only malformed rows", {
    .input = "name,department,salary\nbroken\nalso,broken\n",
    .output = "no data\n",
});
