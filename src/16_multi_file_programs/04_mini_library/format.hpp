// Part of 16_multi_file_programs/04_mini_library; the overview is in todo_list.hpp.

#pragma once

#include <string>

#include "task.hpp"

// A forward declaration is enough here: this header only mentions TodoList by
// reference, so it doesn't need the full class. format.cpp includes todo_list.hpp.
class TodoList;

namespace format {

// Return one line for a task: a checkbox, then its id, title and priority.
// The box is "[ ]" while the task is pending and "[x]" once it's done.
//
// Example:
//   Task task{2, "Buy milk", Priority::High, false};
//   format::task_line(task) is "[ ] #2 Buy milk (high)"
//   task.done = true;
//   format::task_line(task) is "[x] #2 Buy milk (high)"
//
// The priority is written with to_string from task.hpp.
std::string task_line(const Task &task);

// Return how many tasks the list has and how many are done, as one line.
// Use "task" for exactly one, and "tasks" for any other number, 0 included.
//
// Example:
//   three tasks, one of them done: "3 tasks, 1 done"
//   one task, not done:            "1 task, 0 done"
//   an empty list:                 "0 tasks, 0 done"
std::string summary(const TodoList &list);

// Return task_line for every pending task, in pending() order.
// Join the lines with '\n', with no trailing newline.
// Return "" when nothing is pending.
//
// Example:
//   list.add("Buy milk");                       // #1, medium
//   list.add("Write report", Priority::High);   // #2
//   list.add("Old task");                       // #3
//   list.complete(3);
//   format::pending_report(list) is "[ ] #2 Write report (high)\n[ ] #1 Buy milk (medium)"
//
// pending() puts the high-priority task first, so #2 comes before #1.
std::string pending_report(const TodoList &list);

}  // namespace format
