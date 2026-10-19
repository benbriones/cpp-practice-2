#include "grader.hpp"
#include "06_containers/05_stacks_and_queues.cpp"

TEST("balanced_brackets: balanced") {
    CHECK_EQ(balanced_brackets("()"), true);
    CHECK_EQ(balanced_brackets("([]{})"), true);
    CHECK_EQ(balanced_brackets("{[()()]}"), true);
}

TEST("balanced_brackets: ignores other characters") {
    CHECK_EQ(balanced_brackets("f(a[1]) { return x; }"), true);
    CHECK_EQ(balanced_brackets("no brackets at all"), true);
    CHECK_EQ(balanced_brackets(""), true);
}

TEST("balanced_brackets: wrong kind or wrong order") {
    CHECK_EQ(balanced_brackets("(]"), false);
    CHECK_EQ(balanced_brackets("([)]"), false);
    CHECK_EQ(balanced_brackets(")("), false);
}

TEST("balanced_brackets: left open or closed too often") {
    CHECK_EQ(balanced_brackets("(("), false);
    CHECK_EQ(balanced_brackets("{[]"), false);
    CHECK_EQ(balanced_brackets("())"), false);
}

TEST("evaluate_rpn: a single number") {
    CHECK_EQ(evaluate_rpn({"42"}), 42);
    CHECK_EQ(evaluate_rpn({"-7"}), -7);
}

TEST("evaluate_rpn: each operator") {
    CHECK_EQ(evaluate_rpn({"3", "4", "+"}), 7);
    CHECK_EQ(evaluate_rpn({"3", "4", "-"}), -1);
    CHECK_EQ(evaluate_rpn({"3", "4", "*"}), 12);
    CHECK_EQ(evaluate_rpn({"7", "2", "/"}), 3);
}

TEST("evaluate_rpn: longer expressions") {
    CHECK_EQ(evaluate_rpn({"3", "4", "+", "2", "*"}), 14);
    CHECK_EQ(evaluate_rpn({"5", "1", "2", "+", "4", "*", "+", "3", "-"}), 14);
    CHECK_EQ(evaluate_rpn({"2", "-3", "*", "10", "+"}), 4);
}

TEST("evaluate_rpn: missing operands") {
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({"1", "+"}));
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({"*"}));
}

TEST("evaluate_rpn: leftover numbers or nothing at all") {
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({"1", "2"}));
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({}));
}

TEST("evaluate_rpn: bad tokens and division by zero") {
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({"2", "x", "+"}));
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({"2", "3", "%"}));
    CHECK_THROWS(std::invalid_argument, evaluate_rpn({"1", "0", "/"}));
}

TEST("last_survivor: classic examples") {
    CHECK_EQ(last_survivor(7, 3), 4);
    CHECK_EQ(last_survivor(5, 2), 3);
    CHECK_EQ(last_survivor(41, 3), 31);
}

TEST("last_survivor: edge cases") {
    CHECK_EQ(last_survivor(1, 5), 1);
    CHECK_EQ(last_survivor(6, 1), 6);
    CHECK_EQ(last_survivor(2, 2), 1);
}
