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

// Return true if every flag in `flags` is also present in `set`.
// Having only some of the flags isn't enough.
// has(set, None) is always true, since None has no flags to check.
//
// Example:
//   using P = Permission;
//   has(P::Read | P::Write | P::Execute, P::Read | P::Execute) is true
//   has(P::Read, P::Read | P::Write) is false   // Write is missing
//   has(P::Write, P::None) is true
bool has(Permission set, Permission flags) {
    throw "TODO";
}

// Return `set` with every flag in `flags` removed.
// Flags in `flags` that aren't in `set` are simply ignored.
//
// Example:
//   using P = Permission;
//   without(P::Read | P::Write | P::Execute, P::Read | P::Execute) is P::Write
//   without(P::Read, P::Write) is P::Read   // there was no Write to remove
//   without(P::Execute, P::Execute) is P::None
//
// This is set difference: the flags in `set` but not in `flags`.
Permission without(Permission set, Permission flags) {
    throw "TODO";
}

// Return `set` as three characters, Unix style.
// The characters are 'r' or '-', then 'w' or '-', then 'x' or '-'.
// '-' marks a flag that isn't in `set`.
//
// Example:
//   using P = Permission;
//   to_string(P::Read | P::Write | P::Execute) is "rwx"
//   to_string(P::Read | P::Execute) is "r-x"
//   to_string(P::Write) is "-w-"
//   to_string(P::None) is "---"
std::string to_string(Permission set) {
    throw "TODO";
}

// Return the Permission that text spells out: the reverse of to_string.
// text must be exactly three characters of the form [r-][w-][x-].
// Throw std::invalid_argument for anything else.
//
// Example:
//   using P = Permission;
//   parse_permissions("r--") is P::Read
//   parse_permissions("-wx") is P::Write | P::Execute
//   parse_permissions("rw")    // throws std::invalid_argument: too short
//   parse_permissions("wrx")   // throws std::invalid_argument: letters out of order
//
// parse_permissions(to_string(p)) == p for every combination of flags.
Permission parse_permissions(std::string_view text) {
    throw "TODO";
}
