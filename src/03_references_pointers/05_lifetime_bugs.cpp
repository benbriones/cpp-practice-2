// Challenge: Lifetime bugs
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
