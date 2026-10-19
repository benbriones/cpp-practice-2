// Exercise: Permission flags
// Optional module: best after module 04 (enum class).
// Several on/off options packed into one byte, like Unix file permissions.
// Each enumerator is a different bit, so values combine with |.
//
// An enum class doesn't convert to an integer by itself:
// static_cast<std::uint8_t>(p) gets the bits, static_cast<Permission>(bits)
// turns them back. The two operators below are given (operator overloading
// gets its own module, 13).
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
