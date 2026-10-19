// === Lesson: Headers, source files and the linker ============================
//
// A C++ program is built in two stages:
//
//   1. Compile: each .cpp file is compiled on its own into an object file. The
//      compiler sees only that file plus what it #includes, and #include is
//      plain text pasting: the header's contents are copied in at that line.
//   2. Link: the linker joins the object files, matching each call to a
//      function with the one place that function is defined.
//
// That's why C++ separates a declaration (the signature: "this exists
// somewhere") from a definition (the body). A call compiles against just the
// declaration, and the linker finds the body later:
//
//     // temperature.hpp: the interface, included by every file that uses it
//     #pragma once
//     double to_kelvin(double celsius);   // declaration
//
//     // temperature.cpp: the implementation, compiled once
//     #include "temperature.hpp"
//     double to_kelvin(double celsius) { return celsius + 273.15; }
//
//     // main.cpp: a user, which only needs the declaration
//     #include "temperature.hpp"
//     int main() { double k = to_kelvin(20); }
//
// The one-definition rule (ODR): a function may be declared any number of
// times, but defined in only one .cpp file of the whole program. Types are
// different: a struct or class definition (like templates and inline
// functions) may appear in every file that needs it, as long as each copy is
// identical. So types live in headers.
//
// The three errors you'll meet, and what each one means:
//
//   redefinition of 'f'    the compiler saw f's body twice in one .cpp file,
//                          usually a header included twice
//   duplicate symbol 'f'   the linker found f defined in two object files,
//                          usually a body in a header that two .cpp files include
//   Undefined symbols "f"  f was declared and called, but nothing defines it
//
// #pragma once (or an old-style #ifndef/#define/#endif include guard) makes a
// header skip itself the second time it's included into the same .cpp. It does
// nothing across different .cpp files, so it fixes the first error, not the
// second.
//
// Read more: https://www.learncpp.com/cpp-tutorial/header-files/
//            https://www.learncpp.com/cpp-tutorial/header-guards/
//
// === Exercise: Split a header from its source file ===========================
// This folder doesn't build yet. Every function below is *defined* in this
// header, and two files include it (geometry.cpp and the tests), so each
// function gets compiled twice. The tests also include this header twice.
//
// Fix it the standard way, running grade after each step to see the next error:
//   1. Add #pragma once above the #include, so a repeated #include is skipped.
//   2. Leave only declarations here, like the one for triangle_perimeter:
//          double circle_area(double radius);
//   3. Move the function bodies into geometry.cpp.
//
// (Marking each function `inline` would also link. That's how header-only
// libraries work, but practise the header/source split here.)
//
// ./grade 16_multi_file_programs/01_split_into_files

#include <cmath>

struct Point {
    double x{};
    double y{};
};

double distance(Point a, Point b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}

double circle_area(double radius) {
    return 3.14159265358979 * radius * radius;
}

Point midpoint(Point a, Point b) {
    return {(a.x + b.x) / 2, (a.y + b.y) / 2};
}

double triangle_perimeter(Point a, Point b, Point c);
