// === Lesson: Common class bugs ===============================================
//
// The bugs below all compile, and some seem to work at first. Most come with a
// compiler warning, which is why the grader lists warnings after the tests.
//
// Initialization order. Members are initialized in the order they're declared
// in the class, whatever order the initializer list is written in. A member set
// from another member that's declared later reads a value that isn't there yet:
//
//     class Window {
//     public:
//         explicit Window(int side) : side_(side), area_(side_ * side_) {}
//     private:
//         int area_;    // declared first, so initialized first, from side_,
//         int side_;    // which doesn't hold a value yet
//     };
//
// Clang reports "field 'side_' will be initialized after field 'area_'" and
// "field 'side_' is uninitialized when used here".
//
// Assigning a variable to itself. When a parameter has the same name as a
// member, the plain name means the parameter, which hides the member:
//
//     struct Player {
//         std::string name;
//         void rename(std::string name) { name = name; }   // the member is untouched
//     };
//
// Clang reports "explicitly assigning value of variable ... to itself". One
// side of such an assignment was always meant to be something else.
//
// Returning a copy when the caller needs the original. Returning by value
// hands back a copy, and changes to a copy vanish with it:
//
//     class Log {
//     public:
//         std::vector<std::string> lines() { return lines_; }   // a copy
//     private:
//         std::vector<std::string> lines_;
//     };
//     log.lines().push_back("hello");   // compiles, but lines_ never changes
//
// A function returning T& hands back the original instead. The same trap hides
// on the calling side: auto x = f(); copies even when f returns a reference,
// while auto& x = f(); keeps the reference. No warning catches this one; a
// failing test does.
//
// Two more classics: a member with no initializer, like int count_;, holds
// garbage until it's assigned, and a reader without const can't be called
// through a const reference.
//
// To hunt bugs: read each failing test's name and its expected/received values,
// then read every warning. The file:line it names is where to look first.
//
// Read more: https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
//            https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
//
// === Exercise: Find the bugs =================================================
// This Gradebook compiles, but it has three bugs. Run grade to see the failing tests,
// and read the compiler warnings it prints: they point straight at two of the bugs.
// Fix all three without renaming anything or changing parameter lists (a return type
// may change).
//
// ./grade 05_classes/04_class_bugs

#include <stdexcept>
#include <string>
#include <vector>

struct Student {
    std::string name;
    std::vector<int> scores;
};

class Gradebook {
public:
    // Students averaging at least `passing` pass; at least passing + 20 earns honors.
    Gradebook(std::string course, double passing)
        : course_(course), passing_(passing), honors_(passing_ + 20) {}

    const std::string& course() const { return course_; }

    void set_course(std::string course) { course = course; }

    double passing_threshold() const { return passing_; }
    double honors_threshold() const { return honors_; }

    void add_student(const std::string& name) { students_.push_back({name, {}}); }

    // The record for `name`, so callers can update it. Throws std::out_of_range if unknown.
    Student student(const std::string& name) {
        for (Student& s : students_) {
            if (s.name == name) return s;
        }
        throw std::out_of_range("no student named " + name);
    }

    void add_score(const std::string& name, int score) { student(name).scores.push_back(score); }

    // Average score, or 0.0 for a student with no scores yet.
    double average(const std::string& name) const {
        const Student& s = find(name);
        if (s.scores.empty()) return 0.0;
        double total = 0.0;
        for (int score : s.scores) total += score;
        return total / static_cast<double>(s.scores.size());
    }

    // "honors", "pass", or "fail".
    std::string standing(const std::string& name) const {
        double avg = average(name);
        if (avg >= honors_) return "honors";
        if (avg >= passing_) return "pass";
        return "fail";
    }

private:
    const Student& find(const std::string& name) const {
        for (const Student& s : students_) {
            if (s.name == name) return s;
        }
        throw std::out_of_range("no student named " + name);
    }

    std::string course_;
    double honors_;
    double passing_;
    std::vector<Student> students_;
};
