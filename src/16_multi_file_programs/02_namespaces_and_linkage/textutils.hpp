// Exercise: Namespaces and internal linkage
// This folder doesn't build yet, for two reasons:
//
//   1. The tests call the library through its namespace, e.g.
//      textutils::count_vowels("..."). Wrap the declarations below, and the
//      definitions in both .cpp files, in  namespace textutils { ... }
//   2. counting.cpp and cleaning.cpp each define a helper called `matches`
//      with the same signature, so the linker finds two definitions. A helper
//      that only one .cpp file uses shouldn't be visible outside that file:
//      put each one in an anonymous namespace  namespace { ... }  (or mark it
//      `static`). That gives it internal linkage.
//
// Grade: grade 16_multi_file_programs/02_namespaces_and_linkage

#pragma once

#include <string>
#include <string_view>

// Number of vowels (a, e, i, o, u in either case).
int count_vowels(std::string_view text);

// Number of space-separated words that start with a vowel.
int count_vowel_words(std::string_view text);

// text with every punctuation character removed.
std::string strip_punctuation(std::string_view text);

// Number of punctuation characters in text.
int count_punctuation(std::string_view text);
