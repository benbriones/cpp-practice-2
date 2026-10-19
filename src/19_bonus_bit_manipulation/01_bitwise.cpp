// === Lesson: Bits and bitwise operators ======================================
//
// Integers are stored in binary, and C++ lets you work on the bits directly.
// Literals can be written in binary or hex, with ' to group digits:
//
//     0b1010'0110    binary for 166         0xA6           hex for the same 166
//     0xFF           eight 1 bits           0x8000'0000    only bit 31 set
//
// The bitwise operators work on every bit position independently:
//
//     a & b     1 where both are 1     0b1100 & 0b1010  is  0b1000
//     a | b     1 where either is 1    0b1100 | 0b1010  is  0b1110
//     a ^ b     1 where they differ    0b1100 ^ 0b1010  is  0b0110
//     ~a        every bit flipped      ~0b1100u         is  0xFFFF'FFF3
//     a << n    shifted left           0b0011 << 2      is  0b1100   (× 4)
//     a >> n    shifted right          0b1100 >> 2      is  0b0011   (÷ 4)
//
// A mask is a value with 1s in the positions you care about. AND with a mask
// keeps just those bits (x & 0x0F is the low four bits), OR with it turns them
// on, XOR flips them, and AND with its complement (~mask) turns them off.
//
// Use unsigned types such as std::uint32_t (from <cstdint>) for bit work:
//
// - Unsigned arithmetic wraps around (0u - 1 is 0xFFFF'FFFF) by definition;
//   signed overflow is undefined behavior.
// - A plain 1 is an int, so 1 << 31 lands on the sign bit and is negative.
//   1u << 31 stays unsigned.
// - Shifting by the type's width or more (x << 32 for 32 bits) is undefined
//   behavior.
// - Types narrower than int are promoted to int first: for std::uint8_t b = 0,
//   ~b is the int -1, not 255.
//
// Precedence trap: == binds tighter than &, so x & mask == 0 means
// x & (mask == 0). Write (x & mask) == 0.
//
// To see the bits while debugging, std::format("{:032b}", x) or
// std::bitset<32>(x).to_string() gives them as text, most significant first.
//
// Read more: https://www.learncpp.com/cpp-tutorial/bitwise-operators/
//
// === Exercise: Bitwise operators =============================================
// Optional module: try it any time after module 01.
// Implement the functions below with & | ^ ~ << >>. Bit 0 is the least
// significant bit; `bit` is always in 0..31. (<bit> has std::popcount and
// friends; write these by hand first.)
//
// ./grade 19_bonus_bit_manipulation/01_bitwise

#include <cstdint>

// x with the given bit set to 1.
std::uint32_t set_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// x with the given bit cleared to 0.
std::uint32_t clear_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// x with the given bit flipped.
std::uint32_t toggle_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// Whether the given bit of x is 1.
bool test_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// How many bits of x are 1: count_set_bits(0b1011) == 3.
int count_set_bits(std::uint32_t x) {
    throw "TODO";
}

// True for 1, 2, 4, 8, ...; false for 0. Bonus: one expression, no loop.
bool is_power_of_two(std::uint32_t x) {
    throw "TODO";
}

// The value of the lowest 1 bit: lowest_set_bit(0b1100) == 0b0100; 0 gives 0.
std::uint32_t lowest_set_bit(std::uint32_t x) {
    throw "TODO";
}
