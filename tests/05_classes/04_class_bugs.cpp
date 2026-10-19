#include "grader.hpp"
#include "05_classes/04_class_bugs.cpp"

TEST("passing threshold comes from the constructor") {
    Gradebook book("CS101", 60);
    CHECK_NEAR(book.passing_threshold(), 60.0);
}

TEST("honors threshold is 20 above passing") {
    Gradebook book("CS101", 60);
    CHECK_NEAR(book.honors_threshold(), 80.0);
    Gradebook strict("CS999", 75);
    CHECK_NEAR(strict.honors_threshold(), 95.0);
}

TEST("set_course renames the course") {
    Gradebook book("CS101", 60);
    book.set_course("CS102");
    CHECK_EQ(book.course(), "CS102");
}

TEST("add_score records the score") {
    Gradebook book("CS101", 60);
    book.add_student("ada");
    book.add_score("ada", 90);
    book.add_score("ada", 70);
    CHECK_NEAR(book.average("ada"), 80.0);
}

TEST("student() returns the real record, not a copy") {
    Gradebook book("CS101", 60);
    book.add_student("ada");
    book.student("ada").scores.push_back(70);
    CHECK_NEAR(book.average("ada"), 70.0);
}

TEST("student() throws std::out_of_range for unknown names") {
    Gradebook book("CS101", 60);
    book.add_student("ada");
    CHECK_THROWS(std::out_of_range, book.student("grace"));
}

TEST("average is 0 before any scores") {
    Gradebook book("CS101", 60);
    book.add_student("ada");
    CHECK_NEAR(book.average("ada"), 0.0);
}

TEST("standing uses both thresholds") {
    Gradebook book("CS101", 60);
    book.add_student("low");
    book.add_student("mid");
    book.add_student("top");
    book.add_score("low", 59);
    book.add_score("mid", 60);
    book.add_score("top", 80);
    CHECK_EQ(book.standing("low"), "fail");
    CHECK_EQ(book.standing("mid"), "pass");
    CHECK_EQ(book.standing("top"), "honors");
}
