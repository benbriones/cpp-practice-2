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

// Return x with the given bit set to 1.
// Bit 0 is the rightmost (least significant) bit, and bit is always in 0..31.
// Every other bit stays the same, and a bit that is already 1 stays 1.
//
// Example:
//   set_bit(0b0100, 1) is 0b0110
//   set_bit(0b0100, 2) is 0b0100   // bit 2 was already 1
//   set_bit(0, 31) is 0x8000'0000
//
// Build the mask from 1u, not 1: 1 << 31 is a negative int.
std::uint32_t set_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// Return x with the given bit cleared to 0.
// Every other bit stays the same, and a bit that is already 0 stays 0.
//
// Example:
//   clear_bit(0b1111, 0) is 0b1110
//   clear_bit(0b1111, 3) is 0b0111
//   clear_bit(0b1010, 0) is 0b1010   // bit 0 was already 0
//   clear_bit(0xFFFF'FFFF, 31) is 0x7FFF'FFFF
std::uint32_t clear_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// Return x with the given bit flipped: a 0 becomes 1, and a 1 becomes 0.
// Every other bit stays the same.
//
// Example:
//   toggle_bit(0b1010, 0) is 0b1011
//   toggle_bit(0b1010, 1) is 0b1000
//   toggle_bit(0, 31) is 0x8000'0000
std::uint32_t toggle_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// Return whether the given bit of x is 1.
// Return false if that bit is 0, whatever the other bits are.
//
// Example:
//   test_bit(0b1010, 1) is true
//   test_bit(0b1010, 2) is false
//   test_bit(0x7FFF'FFFF, 31) is false   // every bit but bit 31 is set
//
// Watch precedence: != binds tighter than &, so x & mask != 0 means x & (mask != 0).
bool test_bit(std::uint32_t x, int bit) {
    throw "TODO";
}

// Return how many bits of x are 1.
// 0 has no bits set, and 0xFFFF'FFFF has all 32 set.
//
// Example:
//   count_set_bits(0b1011) is 3
//   count_set_bits(0xFF) is 8
//   count_set_bits(0x8000'0001) is 2   // bit 31 and bit 0
//
// std::popcount from <bit> does this too, but write it by hand first.
int count_set_bits(std::uint32_t x) {
    throw "TODO";
}

// Return true if x is a power of two: 1, 2, 4, 8, and so on up to 0x8000'0000.
// Return false for 0.
// A power of two has exactly one bit set.
//
// Example:
//   is_power_of_two(64) is true    // 0b0100'0000
//   is_power_of_two(6) is false    // 0b0110 has two bits set
//   is_power_of_two(0) is false
//
// Bonus: write it as one expression, with no loop.
bool is_power_of_two(std::uint32_t x) {
    throw "TODO";
}

// Return the value of the lowest 1 bit in x, with every other bit cleared.
// If x is 0, return 0.
//
// Example:
//   lowest_set_bit(0b1100) is 0b0100
//   lowest_set_bit(0b1011) is 0b0001
//   lowest_set_bit(0x8000'0000) is 0x8000'0000
//   lowest_set_bit(0) is 0
//
// It returns the bit's value, not its position: 0b0100 (4) for 0b1100, not 2.
std::uint32_t lowest_set_bit(std::uint32_t x) {
    throw "TODO";
}
