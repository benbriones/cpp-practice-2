#include "grader.hpp"
#include "02_strings_vectors/05_word_count.cpp"

PROGRAM_TEST("A short paragraph", {
    .input = "the cat sat\non an elephant\nthe end\n",
    .output = "lines: 3\nwords: 8\nlongest: elephant\n",
});

PROGRAM_TEST("Extra spaces and tabs between words", {
    .input = "  lots   of\tspace  \n",
    .output = "lines: 1\nwords: 3\nlongest: space\n",
});

PROGRAM_TEST("Blank lines count as lines", {
    .input = "one\n\ntwo\n\n",
    .output = "lines: 4\nwords: 2\nlongest: one\n",
});

PROGRAM_TEST("Ties keep the first longest word", {
    .input = "abc xyz\nqrs\n",
    .output = "lines: 2\nwords: 3\nlongest: abc\n",
});

PROGRAM_TEST("Punctuation is part of a word", {
    .input = "Hello, world!\n",
    .output = "lines: 1\nwords: 2\nlongest: Hello,\n",
});

PROGRAM_TEST("Last line without a newline", {
    .input = "first line\nsecond",
    .output = "lines: 2\nwords: 3\nlongest: second\n",
});

PROGRAM_TEST("Empty input", {
    .input = "",
    .output = "lines: 0\nwords: 0\nlongest: (none)\n",
});
