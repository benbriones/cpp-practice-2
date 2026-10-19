// A small demo of the library (given). Run it: grade --run 16_multi_file_programs/04_mini_library

#include <iostream>

#include "format.hpp"
#include "todo_list.hpp"

int main() {
    TodoList list;
    list.add("Write the report", Priority::High);
    const int milk = list.add("Buy milk");
    list.add("Water the plants", Priority::Low);
    list.add("Book flights", Priority::High);
    list.complete(milk);

    std::cout << format::summary(list) << '\n';
    std::cout << format::pending_report(list) << '\n';
}
