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

// "low", "medium", or "high".
std::string to_string(Priority priority);

// The reverse of to_string, ignoring case: "HIGH" gives Priority::High.
// Anything else gives std::nullopt.
std::optional<Priority> parse_priority(std::string_view text);
