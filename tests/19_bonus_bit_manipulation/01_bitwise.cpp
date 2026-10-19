#include "grader.hpp"
#include "19_bonus_bit_manipulation/01_bitwise.cpp"

TEST("set_bit") {
    CHECK_EQ(set_bit(0b0000, 0), 0b0001u);
    CHECK_EQ(set_bit(0b0100, 1), 0b0110u);
    CHECK_EQ(set_bit(0b0100, 2), 0b0100u);
}

TEST("set_bit: the top bit") {
    CHECK_EQ(set_bit(0, 31), 0x8000'0000u);
}

TEST("clear_bit") {
    CHECK_EQ(clear_bit(0b1111, 0), 0b1110u);
    CHECK_EQ(clear_bit(0b1111, 3), 0b0111u);
    CHECK_EQ(clear_bit(0b1010, 0), 0b1010u);
    CHECK_EQ(clear_bit(0xFFFF'FFFFu, 31), 0x7FFF'FFFFu);
}

TEST("toggle_bit") {
    CHECK_EQ(toggle_bit(0b1010, 0), 0b1011u);
    CHECK_EQ(toggle_bit(0b1010, 1), 0b1000u);
    CHECK_EQ(toggle_bit(0, 31), 0x8000'0000u);
}

TEST("test_bit") {
    CHECK_EQ(test_bit(0b1010, 1), true);
    CHECK_EQ(test_bit(0b1010, 2), false);
    CHECK_EQ(test_bit(0x8000'0000u, 31), true);
    CHECK_EQ(test_bit(0x7FFF'FFFFu, 31), false);
}

TEST("count_set_bits") {
    CHECK_EQ(count_set_bits(0), 0);
    CHECK_EQ(count_set_bits(0b1011), 3);
    CHECK_EQ(count_set_bits(0xFF), 8);
    CHECK_EQ(count_set_bits(0xFFFF'FFFFu), 32);
    CHECK_EQ(count_set_bits(0x8000'0001u), 2);
}

TEST("is_power_of_two") {
    CHECK_EQ(is_power_of_two(1), true);
    CHECK_EQ(is_power_of_two(64), true);
    CHECK_EQ(is_power_of_two(0x8000'0000u), true);
    CHECK_EQ(is_power_of_two(0), false);
    CHECK_EQ(is_power_of_two(6), false);
    CHECK_EQ(is_power_of_two(0xFFFF'FFFFu), false);
}

TEST("lowest_set_bit") {
    CHECK_EQ(lowest_set_bit(0b1100), 0b0100u);
    CHECK_EQ(lowest_set_bit(0b1011), 0b0001u);
    CHECK_EQ(lowest_set_bit(0x8000'0000u), 0x8000'0000u);
    CHECK_EQ(lowest_set_bit(0), 0u);
}
