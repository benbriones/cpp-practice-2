// Challenge: Expression calculator
// Evaluate arithmetic like "2 + 3 * (4 - 1.5)" in two stages.
//
// 1. tokenize: text → tokens. A number is one or more digits, optionally
//    followed by '.' and one or more digits ("3", "2.75"; not "2." or ".5").
//    Whitespace between tokens is skipped. Anything else throws
//    std::invalid_argument.
// 2. evaluate: parse the tokens by recursive descent, one function per rule,
//    each consuming tokens from a shared position:
//        expression := term   (('+' | '-') term)*
//        term       := factor (('*' | '/') factor)*
//        factor     := number | '(' expression ')' | '-' factor
//    The grammar gives * and / precedence over + and -, makes operators left
//    associative (8 - 3 - 2 == 3), and allows unary minus (2 * -3 == -6).
//    Throw std::invalid_argument for any syntax error (empty input, missing
//    operand, unbalanced parentheses, leftover tokens) and std::domain_error
//    for division by zero.
//
// Suggested shape: a small Parser class holding the tokens and an index.
//
// ./grade 18_capstone_projects/02_expression_calculator

#include <cctype>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

enum class TokenKind { Number, Plus, Minus, Star, Slash, LeftParen, RightParen };

struct Token {
    TokenKind kind;
    double value = 0;  // only used by Number tokens

    bool operator==(const Token&) const = default;
};

// Given: prints a token in test messages, e.g. Number(2.5) or Plus.
std::ostream& operator<<(std::ostream& out, const Token& token) {
    switch (token.kind) {
        case TokenKind::Number: return out << "Number(" << token.value << ")";
        case TokenKind::Plus: return out << "Plus";
        case TokenKind::Minus: return out << "Minus";
        case TokenKind::Star: return out << "Star";
        case TokenKind::Slash: return out << "Slash";
        case TokenKind::LeftParen: return out << "LeftParen";
        case TokenKind::RightParen: return out << "RightParen";
    }
    return out;
}

std::vector<Token> tokenize(std::string_view text) {
    throw "TODO";
}

double evaluate(std::string_view text) {
    throw "TODO";
}
