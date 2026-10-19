// === Lesson: Organizing a library across files ===============================
//
// Real projects split code into components. Each has a header that declares
// its interface and a .cpp file of the same name that implements it. A .cpp
// file includes its own header first, which proves the header compiles on its
// own, without help from includes that happen to come before it.
//
// Include what you use, and no more. Every #include is text the compiler must
// read again, and every file that includes a header is rebuilt when that
// header changes.
//
// Forward declarations: to mention a class by reference or pointer, the
// compiler only needs to know that the name is a class:
//
//     // report.hpp
//     class Account;                                  // "Account is a class"
//     std::string describe(const Account& account);   // fine: just a reference
//
//     // report.cpp
//     #include "report.hpp"
//     #include "account.hpp"   // the full class, needed to call its members
//     std::string describe(const Account& account) { return account.owner(); }
//
// You need the full definition (its #include) to create an object, hold one by
// value as a member, call a member function, or use sizeof. Declaring a
// function that takes one by reference, or storing a pointer to one, doesn't.
//
// Forward declarations also break include cycles. If a.hpp includes b.hpp and
// b.hpp includes a.hpp, #pragma once lets only one of them go first, and the
// other then uses names it hasn't seen yet.
//
// Building by hand: each .cpp file compiles separately, then they're linked.
// After an edit only the changed files need recompiling, which is what build
// tools like make and CMake automate:
//
//     c++ -std=c++20 -c account.cpp report.cpp main.cpp   # makes three .o files
//     c++ account.o report.o main.o -o app                 # links them
//
// Exactly one .cpp file in a program defines main().
//
// Read more: https://www.learncpp.com/cpp-tutorial/programs-with-multiple-code-files/
//            https://www.learncpp.com/cpp-tutorial/forward-declarations/
//
// === Challenge: A small library in several files =============================
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
// ./grade 16_multi_file_programs/04_mini_library
// Try it: ./grade --run 16_multi_file_programs/04_mini_library

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
