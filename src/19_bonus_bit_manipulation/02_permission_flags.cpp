// === Lesson: Bit flags =======================================================
//
// A set of on/off options fits in one integer: give each option its own bit,
// and a combination is several bits set at once. Unix file permissions and
// text styles both work this way:
//
//     enum class Style : std::uint8_t {
//         None = 0,
//         Bold = 1 << 0,        // 0b001
//         Italic = 1 << 1,      // 0b010
//         Underline = 1 << 2,   // 0b100
//     };
//
// An enum class has no operators and doesn't convert to a number by itself,
// so cast to its underlying type for bit work, and cast the result back:
//
//     auto bits = static_cast<std::uint8_t>(Style::Bold) |
//                 static_cast<std::uint8_t>(Style::Underline);   // 0b101, an int
//     Style both = static_cast<Style>(bits);
//
// both matches no enumerator, and that's fine: an enum with a fixed underlying
// type (the ": std::uint8_t") can hold any value of that type. Code that uses
// flags a lot defines operator| and operator& for the enum once, as this file
// does, so you can write Style::Bold | Style::Underline.
//
// Set operations on flags, as bit operations:
//
//     a | b     the flags in a or b, or both   (union)
//     a & b     only the flags in both         (intersection)
//     a & ~b    the flags in a but not in b    (difference)
//
// Testing for a combination of flags needs a decision: should any of them be
// enough, or must all of them be present? a & b keeps the shared flags; think
// about what that result looks like in each case.
//
// Two std::uint8_t surprises. Arithmetic and ~ promote it to int first, so ~x
// has 24 extra 1 bits until you cast it back to std::uint8_t. And std::cout
// prints it as a character: std::uint8_t{65} prints A. Print +x or int{x} to
// see the number.
//
// Read more: https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/
//            https://www.learncpp.com/cpp-tutorial/bitwise-operators/
//
// === Exercise: Permission flags ==============================================
// Optional module: best after module 04 (enum class).
// Several on/off options packed into one byte, like Unix file permissions.
// The two operators below are given (operator overloading gets its own
// module, 13).
//
// ./grade 19_bonus_bit_manipulation/02_permission_flags

#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

enum class Permission : std::uint8_t {
    None = 0,
    Read = 1,
    Write = 2,
    Execute = 4,
};

// Given: combine flags, and keep only the flags two sets share.
Permission operator|(Permission a, Permission b) {
    return static_cast<Permission>(static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b));
}

Permission operator&(Permission a, Permission b) {
    return static_cast<Permission>(static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b));
}

// True if every flag in `flags` is present in `set`. has(set, None) is true.
bool has(Permission set, Permission flags) {
    throw "TODO";
}

// `set` with every flag in `flags` removed.
Permission without(Permission set, Permission flags) {
    throw "TODO";
}

// Three characters, Unix style: "rwx", "r-x", "---".
std::string to_string(Permission set) {
    throw "TODO";
}

// The reverse of to_string. Anything other than exactly three characters of
// the form [r-][w-][x-] throws std::invalid_argument.
Permission parse_permissions(std::string_view text) {
    throw "TODO";
}
