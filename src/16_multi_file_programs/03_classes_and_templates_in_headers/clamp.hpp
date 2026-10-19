// clamp_value(value, low, high): value limited to the range [low, high].
// Part of 16_multi_file_programs/03; the instructions are in inventory.hpp.

#pragma once

template <typename T>
T clamp_value(T value, T low, T high);
