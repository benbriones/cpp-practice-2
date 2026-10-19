// Part of 16_multi_file_programs/04_mini_library; the overview is in todo_list.hpp.

#pragma once

#include <string>

#include "task.hpp"

// A forward declaration is enough here: this header only mentions TodoList by
// reference, so it doesn't need the full class. format.cpp includes todo_list.hpp.
class TodoList;

namespace format {

// One line for a task: "[ ] #2 Buy milk (high)", or "[x] #2 Buy milk (high)" once done.
std::string task_line(const Task& task);

// "3 tasks, 1 done". Use "task" for exactly one: "1 task, 0 done". Empty: "0 tasks, 0 done".
std::string summary(const TodoList& list);

// task_line for every pending task, in pending() order, joined with '\n' and
// with no trailing newline. "" when nothing is pending.
std::string pending_report(const TodoList& list);

}  // namespace format
