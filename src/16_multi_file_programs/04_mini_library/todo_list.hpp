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
    // Add a task and return its id.
    // Ids start at 1 and count up by one for each task added.
    // An id is never reused, even after its task is removed.
    //
    // Example:
    //   list.add("one") returns 1   // priority defaults to Medium
    //   list.add("two", Priority::High) returns 2
    //   list.remove(2);
    //   list.add("three") returns 3, not 2
    int add(const std::string& title, Priority priority = Priority::Medium);

    // Mark the task with this id as done and return true.
    // Return false if there's no task with that id.
    //
    // Example:
    //   const int id = list.add("Buy milk");
    //   list.complete(id) returns true, and list.find(id)->done is now true
    //   list.complete(42) returns false
    bool complete(int id);

    // Delete the task with this id and return true.
    // Return false if there's no task with that id.
    //
    // Example:
    //   list.add("a");                  // id 1
    //   const int b = list.add("b");    // id 2
    //   list.remove(b) returns true; size() is now 1 and find(b) is nullptr
    //   list.remove(b) returns false, since it's already gone
    bool remove(int id);

    // Return a pointer to the task with this id, or nullptr if there isn't one.
    //
    // Example:
    //   list.add("Buy milk");                       // id 1
    //   list.add("Write report", Priority::High);   // id 2
    //   list.find(2)->title is "Write report"
    //   list.find(99) is nullptr
    //
    // A pointer can say "none" with nullptr, which a reference can't.
    const Task* find(int id) const;

    // Return copies of the tasks not yet done.
    // Put the highest priority first; tasks with the same priority go by id, lowest first.
    //
    // Example:
    //   ids 1 to 5 have priorities Low, Medium, High, High, High
    //   list.complete(5);
    //   pending() gives the tasks with ids {3, 4, 2, 1}
    //
    // They're copies, so sorting them doesn't reorder the list itself.
    std::vector<Task> pending() const;

    // Return the number of tasks, done or not.
    //
    // Example:
    //   add three tasks and complete one: size() is 3
    std::size_t size() const;

    // Return the number of tasks marked done.
    //
    // Example:
    //   add three tasks and complete one: done_count() is 1
    std::size_t done_count() const;

private:
    std::vector<Task> tasks_;
    // TODO: add whatever else you need to hand out ids.
};
