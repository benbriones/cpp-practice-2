// === Lesson: Lifetimes and dangling ==========================================
//
// Every object in C++ has a lifetime, and nothing extends it for you: there's
// no garbage collector keeping an object alive while something still refers to
// it. A reference, pointer, iterator or string_view to an object whose lifetime
// has ended is dangling, and using it is undefined behavior. It may print the
// right answer, print garbage or crash, and that can change from run to run.
//
// Three common ways to end up with one:
//
// 1. Referring to a local after its function returns. Locals are destroyed at
//    the closing brace:
//
//        const std::vector<int>& evens(int n) {
//            std::vector<int> result;
//            for (int i = 0; i <= n; i += 2) result.push_back(i);
//            return result;            // result is destroyed right here
//        }
//
//    Returning by value is the usual answer, and it's cheap: the compiler builds
//    the result directly in the caller or moves it, without copying elements.
//    Return a reference only to something that outlives the call.
//
// 2. Viewing a temporary. A temporary lives until the end of the full
//    expression, the ;. A string_view kept after that dangles:
//
//        std::string_view sv = std::string("ab") + "cd";   // dangles at the ;
//
//    A container of string_views is only valid while every viewed string lives.
//
// 3. Growing a container. When a std::vector runs out of room, push_back moves
//    every element to a new, bigger block and frees the old one. Then every
//    pointer, reference and iterator into the vector dangles, including the
//    hidden iterators of a range-for loop over it:
//
//        std::vector<int> v{1, 2, 3};
//        int& first = v[0];
//        v.push_back(4);         // may reallocate
//        first = 10;             // may write into freed memory
//
// Reading the reports: heap-use-after-free means freed heap memory, and
// stack-use-after-return means a local of a function that already returned.
// When the report points into the test file, your function handed back
// something that was already dangling. Short strings keep their characters
// inside the std::string object itself (the small-string optimization), so one
// bug can be reported as a stack error for short text and a heap error for long
// text. clang catches some of these at compile time, too: read the warnings
// grade lists after the results.
//
// Read more: https://www.learncpp.com/cpp-tutorial/lvalue-references/
//            https://www.learncpp.com/cpp-tutorial/introduction-to-iterators/
//
// === Challenge: Lifetime bugs ================================================
// This file compiles and every function looks reasonable, but each one has a
// lifetime bug: it uses memory after that memory is gone. Run grade to see
// what the address sanitizer reports, then fix all four.
//
// Keep each function's name and parameters. Where a comment says so, you may
// change the return type.
//
// ./grade 03_references_pointers/05_lifetime_bugs

#include <cctype>
#include <string>
#include <string_view>
#include <vector>

// Appends a doubled copy of every element: {1, 2, 3} becomes {1, 2, 3, 2, 4, 6}.
void append_doubles(std::vector<int>& values) {
    for (int x : values) {
        values.push_back(x * 2);
    }
}

// "Hello, Ada! Welcome to the course." for name "Ada".
// (You may change the return type.)
std::string_view make_greeting(const std::string& name) {
    std::string greeting = "Hello, " + name + "! Welcome to the course.";
    return greeting;
}

// The first name in the list, or "anonymous user (no name given)" if the list is empty.
// (You may change the return type.)
const std::string& first_or_default(const std::vector<std::string>& names) {
    std::string fallback = "anonymous user (no name given)";
    if (names.empty()) {
        return fallback;
    }
    return names[0];
}

std::string to_upper(std::string text) {
    for (char& c : text) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return text;
}

// Every word in upper case: {"hi", "there"} becomes {"HI", "THERE"}.
// (You may change the vector's element type.)
std::vector<std::string_view> shout_all(const std::vector<std::string>& words) {
    std::vector<std::string_view> shouted;
    for (const std::string& word : words) {
        std::string upper = to_upper(word);
        shouted.push_back(upper);
    }
    return shouted;
}
