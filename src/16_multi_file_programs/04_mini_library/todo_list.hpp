// Challenge: A small library in several files
// A to-do list library laid out the way real projects are: each header declares
// an interface, and the .cpp with the same name implements it.
//
//   task.hpp / task.cpp             Task, Priority, and converting priorities to and from text
//   todo_list.hpp / todo_list.cpp   TodoList, the collection of tasks (this file)
//   format.hpp / format.cpp         text output, in namespace format
//   main.cpp                        a small demo program (given)
//
// Implement every function that throws "TODO" in the three .cpp files. The
// requirements are in the comments next to each declaration in the headers.
//
// Grade: grade 16_multi_file_programs/04_mini_library
// Try it: grade --run 16_multi_file_programs/04_mini_library

#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "task.hpp"

class TodoList {
public:
    // Add a task and return its id. Ids start at 1 and count up; an id is never
    // reused, even after its task is removed.
    int add(const std::string& title, Priority priority = Priority::Medium);

    // Mark the task done. Return false if there's no task with that id.
    bool complete(int id);

    // Delete the task. Return false if there's no task with that id.
    bool remove(int id);

    // The task with this id, or nullptr if there isn't one.
    const Task* find(int id) const;

    // Copies of the tasks not yet done: highest priority first, ties by id.
    std::vector<Task> pending() const;

    // Number of tasks, done or not.
    std::size_t size() const;

    // Number of tasks marked done.
    std::size_t done_count() const;

private:
    std::vector<Task> tasks_;
    // TODO: add whatever else you need to hand out ids.
};
