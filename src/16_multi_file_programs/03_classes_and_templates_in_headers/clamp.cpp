// Part of 16_multi_file_programs/03; the instructions are in inventory.hpp.

#include "clamp.hpp"

template <typename T>
T clamp_value(T value, T low, T high) {
    if (value < low) return low;
    if (high < value) return high;
    return value;
}
