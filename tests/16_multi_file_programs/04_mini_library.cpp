#include "grader.hpp"
#include "16_multi_file_programs/04_mini_library/format.hpp"
#include "16_multi_file_programs/04_mini_library/todo_list.hpp"

#include <string>
#include <vector>

std::vector<int> ids(const std::vector<Task>& tasks) {
    std::vector<int> out;
    for (const Task& task : tasks) out.push_back(task.id);
    return out;
}

TEST("to_string(Priority)") {
    CHECK_EQ(to_string(Priority::Low), "low");
    CHECK_EQ(to_string(Priority::Medium), "medium");
    CHECK_EQ(to_string(Priority::High), "high");
}

TEST("parse_priority ignores case") {
    CHECK_EQ(parse_priority("low"), Priority::Low);
    CHECK_EQ(parse_priority("Medium"), Priority::Medium);
    CHECK_EQ(parse_priority("HIGH"), Priority::High);
}

TEST("parse_priority rejects anything else") {
    CHECK_EQ(parse_priority("urgent"), std::nullopt);
    CHECK_EQ(parse_priority(""), std::nullopt);
    CHECK_EQ(parse_priority("high "), std::nullopt);
}

TEST("TodoList::add returns increasing ids from 1") {
    TodoList list;
    CHECK_EQ(list.add("one"), 1);
    CHECK_EQ(list.add("two", Priority::High), 2);
    CHECK_EQ(list.add("three"), 3);
    CHECK_EQ(list.size(), 3);
}

TEST("TodoList::find") {
    TodoList list;
    list.add("Buy milk");
    const int report = list.add("Write report", Priority::High);
    const Task* task = list.find(report);
    CHECK(task != nullptr, "find(2) returned nullptr");
    CHECK_EQ(task->id, 2);
    CHECK_EQ(task->title, "Write report");
    CHECK_EQ(task->priority, Priority::High);
    CHECK_EQ(task->done, false);
    CHECK_EQ(list.find(99), nullptr);
}

TEST("TodoList::complete") {
    TodoList list;
    const int id = list.add("Buy milk");
    CHECK_EQ(list.complete(id), true);
    CHECK_EQ(list.find(id)->done, true);
    CHECK_EQ(list.done_count(), 1);
    CHECK_EQ(list.complete(42), false);
}

TEST("TodoList::remove, and ids are never reused") {
    TodoList list;
    list.add("a");
    const int b = list.add("b");
    CHECK_EQ(list.remove(b), true);
    CHECK_EQ(list.size(), 1);
    CHECK_EQ(list.find(b), nullptr);
    CHECK_EQ(list.remove(b), false);
    CHECK_EQ(list.add("c"), 3);
}

TEST("TodoList::pending: highest priority first, then by id") {
    TodoList list;
    list.add("low", Priority::Low);
    list.add("medium");
    list.add("high", Priority::High);
    list.add("another high", Priority::High);
    list.add("done", Priority::High);
    list.complete(5);
    CHECK_EQ(ids(list.pending()), {3, 4, 2, 1});
}

TEST("format::task_line") {
    Task task{2, "Buy milk", Priority::High, false};
    CHECK_EQ(format::task_line(task), "[ ] #2 Buy milk (high)");
    task.done = true;
    CHECK_EQ(format::task_line(task), "[x] #2 Buy milk (high)");
    CHECK_EQ(format::task_line({17, "Nap", Priority::Low, false}), "[ ] #17 Nap (low)");
}

TEST("format::summary") {
    TodoList list;
    CHECK_EQ(format::summary(list), "0 tasks, 0 done");
    list.add("a");
    CHECK_EQ(format::summary(list), "1 task, 0 done");
    list.add("b");
    list.add("c");
    list.complete(1);
    CHECK_EQ(format::summary(list), "3 tasks, 1 done");
}

TEST("format::pending_report") {
    TodoList list;
    CHECK_EQ(format::pending_report(list), "");
    list.add("Buy milk");
    list.add("Write report", Priority::High);
    list.add("Old task");
    list.complete(3);
    CHECK_EQ(format::pending_report(list), "[ ] #2 Write report (high)\n[ ] #1 Buy milk (medium)");
}
