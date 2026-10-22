// Part of 16_multi_file_programs/03; the instructions are in inventory.hpp.

#pragma once

// Return value limited to the range [low, high].
// Below low gives low, above high gives high, and anything in between gives value.
// It works for any type that can be compared with <.
//
// Example:
//   clamp_value(5, 0, 10) is 5
//   clamp_value(-5, 0, 10) is 0
//   clamp_value(1.5, 0.0, 1.0) is 1.0
//   clamp_value('z', 'a', 'm') is 'm'
template <typename T>
T clamp_value(T value, T low, T high);
