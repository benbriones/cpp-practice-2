// Challenge: Color packing
// Optional module: best after module 04 (structs).
// Graphics code stores a color as one 32-bit number, 0xRRGGBBAA: red in the
// top byte, alpha (opacity) in the bottom one. Pack and unpack it with shifts
// and masks: (packed >> 8) & 0xFF is the blue byte.
//
// ./grade 19_bonus_bit_manipulation/03_color_packing

#include <bitset>
#include <cstdint>
#include <format>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

struct Color {
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 255;

    bool operator==(const Color&) const = default;
};

// Given: prints Color(255, 128, 0, 255) in test messages.
std::ostream& operator<<(std::ostream& out, const Color& c) {
    return out << "Color(" << int{c.r} << ", " << int{c.g} << ", " << int{c.b} << ", " << int{c.a} << ")";
}

// Color{0x12, 0x34, 0x56, 0x78} packs to 0x12345678.
std::uint32_t pack(Color c) {
    throw "TODO";
}

Color unpack(std::uint32_t packed) {
    throw "TODO";
}

// "#RRGGBBAA" with upper-case hex digits. std::format("{:02X}", n) formats one byte.
std::string to_hex(Color c) {
    throw "TODO";
}

// The reverse of to_hex; lower-case digits are accepted too. Anything that
// isn't '#' plus exactly 8 hex digits throws std::invalid_argument.
Color from_hex(std::string_view text) {
    throw "TODO";
}

// Average each channel of two colors, rounding down.
// Bonus: on packed numbers, (x & y) + (((x ^ y) & 0xFEFEFEFE) >> 1) averages
// all four bytes at once. Work out why it does before you use it.
Color blend(Color x, Color y) {
    throw "TODO";
}

// The channels as binary, separated by spaces: "11111111 10000000 00000000 11111111".
// std::bitset<8>(value).to_string() writes one byte.
std::string to_binary(Color c) {
    throw "TODO";
}
