#include "grader.hpp"
#include "01_basics/02_conditions.cpp"

TEST("is_leap_year: ordinary years") {
    CHECK_EQ(is_leap_year(2024), true);
    CHECK_EQ(is_leap_year(2023), false);
}

TEST("is_leap_year: centuries") {
    CHECK_EQ(is_leap_year(1900), false);
    CHECK_EQ(is_leap_year(2100), false);
    CHECK_EQ(is_leap_year(2000), true);
}

TEST("days_in_month: 31- and 30-day months") {
    CHECK_EQ(days_in_month(1, 2023), 31);
    CHECK_EQ(days_in_month(4, 2023), 30);
    CHECK_EQ(days_in_month(7, 2023), 31);
    CHECK_EQ(days_in_month(11, 2023), 30);
    CHECK_EQ(days_in_month(12, 2023), 31);
}

TEST("days_in_month: February") {
    CHECK_EQ(days_in_month(2, 2023), 28);
    CHECK_EQ(days_in_month(2, 2024), 29);
    CHECK_EQ(days_in_month(2, 1900), 28);
}

TEST("days_in_month: invalid month") {
    CHECK_EQ(days_in_month(0, 2023), 0);
    CHECK_EQ(days_in_month(13, 2023), 0);
}

TEST("letter_grade: each band") {
    CHECK_EQ(letter_grade(95), 'A');
    CHECK_EQ(letter_grade(85), 'B');
    CHECK_EQ(letter_grade(75), 'C');
    CHECK_EQ(letter_grade(65), 'D');
    CHECK_EQ(letter_grade(10), 'F');
}

TEST("letter_grade: boundaries") {
    CHECK_EQ(letter_grade(90), 'A');
    CHECK_EQ(letter_grade(89), 'B');
    CHECK_EQ(letter_grade(60), 'D');
    CHECK_EQ(letter_grade(59), 'F');
    CHECK_EQ(letter_grade(100), 'A');
    CHECK_EQ(letter_grade(0), 'F');
}

TEST("letter_grade: out of range") {
    CHECK_EQ(letter_grade(101), '?');
    CHECK_EQ(letter_grade(-1), '?');
}

TEST("classify_triangle: valid triangles") {
    CHECK_EQ(classify_triangle(3, 3, 3), "equilateral");
    CHECK_EQ(classify_triangle(3, 3, 5), "isosceles");
    CHECK_EQ(classify_triangle(5, 3, 3), "isosceles");
    CHECK_EQ(classify_triangle(3, 4, 5), "scalene");
}

TEST("classify_triangle: invalid sides") {
    CHECK_EQ(classify_triangle(0, 4, 5), "invalid");
    CHECK_EQ(classify_triangle(3, -4, 5), "invalid");
    CHECK_EQ(classify_triangle(1, 2, 3), "invalid");
    CHECK_EQ(classify_triangle(10, 2, 3), "invalid");
}
