// === Lesson: Packing fields into an integer ==================================
//
// Several small values can share one integer, each in its own range of bits.
// A date fits in 32 bits: year in bits 16-31, month in bits 8-15, day in 0-7.
//
//     2024-03-15   →   0x07E8'030F      (0x07E8 is 2024, 0x03 is 3, 0x0F is 15)
//
// To unpack a field, shift it down to bit 0, then mask off everything above:
//
//     std::uint32_t date = 0x07E8'030F;
//     unsigned month = (date >> 8) & 0xFF;   // 0x03
//     unsigned year = date >> 16;            // nothing above it to mask off
//
// To pack, widen each field to the result type, shift it into place, and
// combine the fields with |. The widening matters for small types: a
// std::uint8_t is promoted to int before it's shifted, so level << 24 is
// signed int arithmetic that only happens to land on the right bits, and
// level << 40 (for a 64-bit layout) is undefined behavior. Widen first:
//
//     std::uint8_t level = 0xC8;
//     std::uint32_t top = std::uint32_t{level} << 24;   // 0xC800'0000
//
// Precedence: << and >> bind tighter than & and |, and == binds tighter than &.
// Parentheses make bit expressions readable anyway.
//
// Hex text. std::format("{:02X}", n) writes n as two upper-case hex digits,
// padded with 0. In the other direction, std::from_chars (from <charconv>)
// parses in any base, and it's strict: no spaces, no 0x prefix, no + sign.
//
//     std::string_view text = "1f";
//     unsigned value = 0;
//     auto [end, error] =
//         std::from_chars(text.data(), text.data() + text.size(), value, 16);
//     // value is 31; error == std::errc{} and end is just past the "f"
//
// std::stoul(s, nullptr, 16) is looser: it skips leading spaces and accepts a
// 0x prefix and a sign, which lets through text a strict parser rejects.
//
// Read more: https://www.learncpp.com/cpp-tutorial/bitwise-operators/
//            https://en.cppreference.com/w/cpp/utility/from_chars
//
// === Challenge: Color packing ================================================
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
