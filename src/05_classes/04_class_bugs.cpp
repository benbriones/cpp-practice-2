// Exercise: Find the bugs
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
