// === Lesson: std::string_view ================================================
//
// std::string_view (from <string_view>) is a read-only window onto characters
// stored somewhere else: a std::string, a string literal, or part of either.
// Inside it's just a pointer and a length, so it's cheap to create and to pass
// by value, and making one copies no characters.
//
//     std::string title = "The C++ Programming Language";
//     std::string_view sv = title;               // views all of title, no copy
//     std::string_view lang = sv.substr(4, 3);   // "C++", still a view into title
//     std::string copy = title.substr(4, 3);     // std::string::substr does copy
//
// It has most of std::string's read-only interface, plus two ways to shrink the
// window in place:
//
//     sv.size()   sv.empty()   sv[i]   sv.front()   sv.back()   for (char c : sv)
//     sv.find('x')           // an index, or std::string_view::npos if not found
//     sv.starts_with("The")  sv.ends_with("age")              // C++20
//     sv.remove_prefix(4);   // the view now starts 4 characters later
//     sv.remove_suffix(9);   // and ends 9 characters earlier
//
// A function that returns part of its input can return a view of it:
//
//     std::string_view extension(std::string_view path) {
//         std::size_t dot = path.rfind('.');
//         if (dot == std::string_view::npos) return {};   // an empty view
//         return path.substr(dot + 1);
//     }
//
//     extension("photo.jpeg") == "jpeg"   // viewing the "jpeg" inside "photo.jpeg"
//
// sv.data() is the address of the first viewed character. That's how a test can
// tell a view into the original text from a view of a copy.
//
// The catch: a view owns nothing, so whatever it views must outlive it.
//
//     std::string_view bad = std::string("temp");   // the string dies at the ;
//     std::string_view name() { std::string s = "x"; return s; }   // dangles
//
// Converting: a std::string becomes a string_view automatically; going the other
// way is an explicit copy, std::string(sv). For <cctype> functions such as
// std::isspace, pass the character as an unsigned char:
// std::isspace(static_cast<unsigned char>(c)).
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/
//            https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/
//
// === Exercise: std::string_view ==============================================
// Implement the four functions below. Each must return a view into its input,
// never a copy.
//
// ./grade 03_references_pointers/04_string_view

#include <cctype>
#include <cstddef>
#include <string_view>

// Number of words: runs of non-whitespace characters.
// count_words("  hi \t there\n") == 2
std::size_t count_words(std::string_view text) {
    throw "TODO";
}

// The first word of text, skipping leading whitespace. Empty if there is none.
// first_word("  hello world") == "hello"
std::string_view first_word(std::string_view text) {
    throw "TODO";
}

// text without its leading and trailing whitespace.
std::string_view trim_view(std::string_view text) {
    throw "TODO";
}

// If text starts with prefix, the rest of text; otherwise text unchanged.
// strip_prefix("unhappy", "un") == "happy"
std::string_view strip_prefix(std::string_view text, std::string_view prefix) {
    throw "TODO";
}
