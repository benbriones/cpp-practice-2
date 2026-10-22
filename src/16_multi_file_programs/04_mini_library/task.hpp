// Part of 16_multi_file_programs/04_mini_library; the overview is in todo_list.hpp.

#pragma once

#include <optional>
#include <string>
#include <string_view>

enum class Priority { Low, Medium, High };

struct Task {
    int id{};
    std::string title;
    Priority priority{Priority::Medium};
    bool done{false};
};

// Return the priority's name in lowercase: "low", "medium", or "high".
//
// Example:
//   to_string(Priority::Low) is "low"
//   to_string(Priority::High) is "high"
std::string to_string(Priority priority);

// Return the Priority that text names: the reverse of to_string, ignoring case.
// Anything else gives std::nullopt, even a name with an extra space.
//
// Example:
//   parse_priority("low") is Priority::Low
//   parse_priority("Medium") is Priority::Medium
//   parse_priority("HIGH") is Priority::High
//   parse_priority("urgent") is std::nullopt
//   parse_priority("high ") is std::nullopt   // the trailing space counts
//
// It returns std::optional, so "no such priority" is a value, not an exception.
std::optional<Priority> parse_priority(std::string_view text);
