// === Lesson: Namespaces and linkage ==========================================
//
// A namespace groups names so they can't collide with names from other code,
// a bit like a module's exports in Python or JavaScript. You refer to its
// members with ::, and you can reopen the same namespace in as many files as
// you like:
//
//     // shapes.hpp
//     namespace shapes {
//     double area_of_circle(double r);
//     }
//
//     // shapes.cpp
//     namespace shapes {
//     double area_of_circle(double r) { return 3.14159 * r * r; }
//     }
//
//     shapes::area_of_circle(2.0);     // a qualified name
//     using shapes::area_of_circle;    // a using-declaration: from here on in
//     area_of_circle(2.0);             // this scope, the plain name works
//
// The definition must be in the same namespace as the declaration (or be
// written as double shapes::area_of_circle(double r) { ... }). A body written
// outside the namespace defines a different, global function, and the linker
// then reports shapes::area_of_circle as undefined.
//
// `using namespace std;` imports every name at once. Keep it out of headers:
// it would leak into every file that includes them.
//
// Linkage decides who can see a name at link time:
//
//   external   the default for functions and global variables. All .cpp files
//              share one name, so two files defining the same function is a
//              "duplicate symbol" error.
//   internal   visible only inside its own .cpp file, so two files can each
//              have a private helper with the same name.
//
// Give a helper internal linkage with an anonymous namespace (preferred), or
// the older `static`:
//
//     namespace {
//     bool is_even(int n) { return n % 2 == 0; }   // private to this .cpp
//     }
//     static int square(int n) { return n * n; }   // same effect
//
// A good habit: anything a .cpp file doesn't declare in a header gets internal
// linkage.
//
// Read more: https://www.learncpp.com/cpp-tutorial/internal-linkage/
//            https://www.learncpp.com/cpp-tutorial/unnamed-and-inline-namespaces/
//
// === Exercise: Namespaces and internal linkage ===============================
// This folder doesn't build yet, for two reasons:
//
//   1. The tests call the library through its namespace, e.g.
//      textutils::count_vowels("..."). Wrap the declarations below, and the
//      definitions in both .cpp files, in  namespace textutils { ... }
//   2. counting.cpp and cleaning.cpp each define a helper called `matches`
//      with the same signature, so the linker finds two definitions. A helper
//      that only one .cpp file uses shouldn't be visible outside that file:
//      give each one internal linkage.
//
// ./grade 16_multi_file_programs/02_namespaces_and_linkage

#pragma once

#include <string>
#include <string_view>

// Return the number of vowels in text.
// The vowels are a, e, i, o and u, in either case; y doesn't count.
//
// Example:
//   count_vowels("Hello World") is 3
//   count_vowels("AEIOU aeiou") is 10
//   count_vowels("rhythm") is 0
int count_vowels(std::string_view text);

// Return the number of space-separated words that start with a vowel.
// Vowels are the same as for count_vowels, in either case. Empty text gives 0.
//
// Example:
//   count_vowel_words("an apple is on the table") is 4   // an, apple, is, on
//   count_vowel_words("Every Other Thing") is 2
//   count_vowel_words("") is 0
int count_vowel_words(std::string_view text);

// Return text with every punctuation character removed.
// Everything else, spaces included, stays in its original order.
//
// Example:
//   strip_punctuation("Hi, there! (ok?)") is "Hi there ok"
//   strip_punctuation("plain") is "plain"
std::string strip_punctuation(std::string_view text);

// Return the number of punctuation characters in text.
//
// Example:
//   count_punctuation("Wait... what?!") is 5   // the three dots, ? and !
//   count_punctuation("none here") is 0
int count_punctuation(std::string_view text);
