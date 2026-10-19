// Challenge: Stacks and queues
// std::stack is last-in-first-out: push, top, pop, empty, size.
// std::queue is first-in-first-out: push, front, pop, empty, size.
// pop() returns nothing in both, so read top()/front() first.
//
// ./grade 06_containers/05_stacks_and_queues

#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// True if every (, [ and { is closed by its matching bracket in the right order.
// Other characters are ignored: "f(a[1]) { }" is balanced; "(]", "((" and ")(" are not.
bool balanced_brackets(std::string_view text) {
    throw "TODO";
}

// Evaluate Reverse Polish Notation: {"3", "4", "+", "2", "*"} means (3 + 4) * 2 == 14.
// A token is an integer (maybe negative, like "-3") or one of + - * / (integer division).
// std::stoi(token) turns "42" into 42 and throws std::invalid_argument for "x".
// Throw std::invalid_argument for an operator without two operands, division by zero,
// an unknown token, or anything other than exactly one number left at the end.
int evaluate_rpn(const std::vector<std::string>& tokens) {
    throw "TODO";
}

// People 1..n stand in a circle. Counting from person 1, every k-th person leaves, and
// counting continues with the next person. Return the number of the last one standing.
// last_survivor(7, 3) == 4: people leave in the order 3, 6, 2, 7, 5, 1.
// Use a std::queue: send people from the front to the back while you count.
int last_survivor(int n, int k) {
    throw "TODO";
}
