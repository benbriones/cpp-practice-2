#include "grader.hpp"
#include "18_capstone_projects/02_expression_calculator.cpp"

using K = TokenKind;

TEST("tokenize: operators and parentheses") {
    CHECK_EQ(tokenize("+-*/()"), {{K::Plus}, {K::Minus}, {K::Star}, {K::Slash}, {K::LeftParen}, {K::RightParen}});
}

TEST("tokenize: numbers") {
    CHECK_EQ(tokenize("42"), {{K::Number, 42}});
    CHECK_EQ(tokenize("2.75"), {{K::Number, 2.75}});
    CHECK_EQ(tokenize("007"), {{K::Number, 7}});
}

TEST("tokenize: skips whitespace") {
    CHECK_EQ(tokenize("  1 +\t2 "), {{K::Number, 1}, {K::Plus}, {K::Number, 2}});
    CHECK_EQ(tokenize("(3)*4"), {{K::LeftParen}, {K::Number, 3}, {K::RightParen}, {K::Star}, {K::Number, 4}});
    CHECK_EQ(tokenize(""), {});
}

TEST("tokenize: rejects bad characters and malformed numbers") {
    CHECK_THROWS(std::invalid_argument, tokenize("2 + x"));
    CHECK_THROWS(std::invalid_argument, tokenize("2 % 3"));
    CHECK_THROWS(std::invalid_argument, tokenize("2."));
    CHECK_THROWS(std::invalid_argument, tokenize(".5"));
    CHECK_THROWS(std::invalid_argument, tokenize("1..2"));
}

TEST("evaluate: single numbers") {
    CHECK_NEAR(evaluate("42"), 42.0);
    CHECK_NEAR(evaluate(" 2.5 "), 2.5);
}

TEST("evaluate: + and - are left associative") {
    CHECK_NEAR(evaluate("1 + 2"), 3.0);
    CHECK_NEAR(evaluate("8 - 3 - 2"), 3.0);
    CHECK_NEAR(evaluate("10 - 4 + 1"), 7.0);
}

TEST("evaluate: * and / bind tighter than + and -") {
    CHECK_NEAR(evaluate("2 + 3 * 4"), 14.0);
    CHECK_NEAR(evaluate("2 * 3 + 4"), 10.0);
    CHECK_NEAR(evaluate("8 / 4 / 2"), 1.0);
    CHECK_NEAR(evaluate("7 / 2"), 3.5);
}

TEST("evaluate: parentheses") {
    CHECK_NEAR(evaluate("(2 + 3) * 4"), 20.0);
    CHECK_NEAR(evaluate("2 * (3 + (4 - 1)) / 3"), 4.0);
    CHECK_NEAR(evaluate("((5))"), 5.0);
}

TEST("evaluate: unary minus") {
    CHECK_NEAR(evaluate("-3"), -3.0);
    CHECK_NEAR(evaluate("2 * -3"), -6.0);
    CHECK_NEAR(evaluate("--4"), 4.0);
    CHECK_NEAR(evaluate("-(2 + 3) * 2"), -10.0);
    CHECK_NEAR(evaluate("5 - -2"), 7.0);
}

TEST("evaluate: decimals") {
    CHECK_NEAR(evaluate("1.5 * 4"), 6.0);
    CHECK_NEAR(evaluate("0.1 + 0.2"), 0.3);
}

TEST("evaluate: syntax errors throw std::invalid_argument") {
    CHECK_THROWS(std::invalid_argument, evaluate(""));
    CHECK_THROWS(std::invalid_argument, evaluate("2 +"));
    CHECK_THROWS(std::invalid_argument, evaluate("* 2"));
    CHECK_THROWS(std::invalid_argument, evaluate("(1 + 2"));
    CHECK_THROWS(std::invalid_argument, evaluate("1 + 2)"));
    CHECK_THROWS(std::invalid_argument, evaluate("2 3"));
    CHECK_THROWS(std::invalid_argument, evaluate("()"));
    CHECK_THROWS(std::invalid_argument, evaluate("2 + y"));
}

TEST("evaluate: division by zero throws std::domain_error") {
    CHECK_THROWS(std::domain_error, evaluate("4 / 0"));
    CHECK_THROWS(std::domain_error, evaluate("1 / (2 - 2)"));
}
