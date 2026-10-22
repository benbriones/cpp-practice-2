// === Lesson: Tokenizers and recursive descent ================================
//
// Most parsers work in two passes. A tokenizer (lexer) turns characters into
// tokens, so the parser never sees spaces or reads a number digit by digit:
//
//     "12 + x1"   →   Number(12), Plus, Name("x1")
//
// A tokenizer is a loop over an index: look at the current character, then
// consume as many characters as that one token needs. Pass chars to <cctype>
// functions as unsigned char, std::isdigit(static_cast<unsigned char>(c)), since
// a negative char is undefined behavior there. std::stod converts a run of text
// you've already checked: std::stod(std::string(text.substr(start, length))).
//
// A recursive descent parser has one function per grammar rule. Each reads
// tokens from a shared position and returns what it parsed. Grammar notation
// maps straight onto code:
//
//     a b        call a, then b
//     a | b      peek at the next token and choose with if/else
//     ( ... )*   a while loop that runs as long as the next token fits
//     ( ... )?   an if
//     nesting    a rule that ends up calling itself: recursion
//
// For example, this grammar sums nested lists of digits like "[1,[2,3],4]":
//
//     list := '[' ( item (',' item)* )? ']'        item := digit | list
//
//     int list() {
//         expect('[');
//         int sum = 0;
//         if (peek() != ']') {         // ( ... )?
//             sum += item();
//             while (peek() == ',') {  // (',' item)*
//                 advance();
//                 sum += item();
//             }
//         }
//         expect(']');
//         return sum;
//     }
//     int item() { return peek() == '[' ? list() : digit(); }
//
// peek() returns the next character without consuming it, advance() moves past
// it, and expect(c) consumes c or throws. They'd be members of a parser class
// that holds the text and the position; with tokens it's the same idea.
//
// Precedence comes from layering: the rule for a looser operator calls the
// rule for a tighter one, so tighter operators are applied first. A loop that
// accumulates as it goes makes an operator left associative.
//
// When the top rule returns, check that all the input was used; otherwise "1 2"
// would quietly parse as 1.
//
// Read more: https://en.wikipedia.org/wiki/Recursive_descent_parser
//
// === Challenge: Expression calculator ========================================
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

    bool operator==(const Token &) const = default;
};

// Given: prints a token in test messages, e.g. Number(2.5) or Plus.
std::ostream &operator<<(std::ostream &out, const Token &token) {
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
