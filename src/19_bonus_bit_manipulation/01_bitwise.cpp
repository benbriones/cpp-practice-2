// Exercise: Bitwise operators
// Optional module: try it any time after module 01.
// Implement the functions below with & | ^ ~ << >>. Bit 0 is the least
// significant bit; `bit` is always in 0..31.
//
// Do bit work with unsigned types like std::uint32_t (from <cstdint>), and
// shift an unsigned one, 1u << bit, so the whole expression stays unsigned.
// (<bit> has std::popcount and friends; write these by hand first.)
//
// Grade: grade 19_bonus_bit_manipulation/01_bitwise

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
