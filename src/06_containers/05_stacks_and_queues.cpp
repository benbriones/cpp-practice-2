// === Lesson: Stacks and queues ===============================================
//
// std::stack and std::queue are container adaptors: thin wrappers around another
// container (a std::deque by default) that only allow stack or queue moves.
//
//     std::stack<T>   last in, first out:   push(x)  top()    pop()  empty()  size()
//     std::queue<T>   first in, first out:  push(x)  front()  pop()  empty()  size()
//                                           (plus back(), the newest element)
//
//     #include <queue>
//     #include <stack>
//
//     std::stack<std::string> undo;      // an editor's undo history
//     undo.push("type 'a'");
//     undo.push("delete line");
//     std::string last = undo.top();     // "delete line": the most recent push
//     undo.pop();                        // removes it, and returns nothing
//
//     std::queue<int> tickets;           // customers waiting in line
//     tickets.push(101);
//     tickets.push(102);
//     int next = tickets.front();        // 101: the oldest push
//     tickets.pop();
//
// pop() returns void, so read top() or front() first. (Returning the removed
// value would mean copying it, and if that copy threw, the value would be lost.)
//
// top(), front() and pop() on an empty stack or queue are undefined behavior,
// not an exception, so check empty() or size() before taking something off.
//
// A stack hands values back in reverse: after push(a) and push(b), the first
// pop gives b. Keep that in mind whenever the order of two popped values
// matters. Stacks suit nested structure, where the most recent unfinished thing
// must be finished first. Queues suit things handled in arrival order.
//
// Parsing integers: std::stoi("42") is 42 (from <string>). It throws
// std::invalid_argument when the text doesn't start with a number, like "x"
// or "+", and std::out_of_range when the number doesn't fit in an int. It stops
// at the first character it can't use, so std::stoi("12ab") is 12. Its second
// argument reports how many characters it used, if you need to reject those:
//
//     std::size_t used = 0;
//     int n = std::stoi(text, &used);    // used == text.size(): it all parsed
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdvector-and-stack-behavior/
//            https://en.cppreference.com/w/cpp/string/basic_string/stol
//
// === Challenge: Stacks and queues ============================================
// Implement the three functions below.
//
// ./grade 06_containers/05_stacks_and_queues

#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// Return true if every (, [ and { is closed by its matching bracket in the right order.
// Other characters are ignored, so text with no brackets at all is balanced.
//
// Example:
//   balanced_brackets("f(a[1]) { }") is true
//   balanced_brackets("(]") is false     // wrong kind of bracket
//   balanced_brackets("([)]") is false   // closed in the wrong order
//   balanced_brackets("((") is false     // left open
//   balanced_brackets(")(") is false     // closed before it was opened
bool balanced_brackets(std::string_view text) {
    throw "TODO";
}

// Evaluate an expression in Reverse Polish Notation and return its value.
// A token is an integer (maybe negative, like "-3") or one of + - * / (integer division).
// std::stoi(token) turns "42" into 42 and throws std::invalid_argument for "x".
// Throw std::invalid_argument for an operator without two operands, division by zero,
// an unknown token, or anything other than exactly one number left at the end.
//
// Example:
//   evaluate_rpn({"3", "4", "+", "2", "*"}) is 14   // (3 + 4) * 2
//   evaluate_rpn({"3", "4", "-"}) is -1             // 3 - 4, not 4 - 3
//   evaluate_rpn({"1", "+"}) throws std::invalid_argument
//   evaluate_rpn({"1", "2"}) throws std::invalid_argument
int evaluate_rpn(const std::vector<std::string> &tokens) {
    throw "TODO";
}

// Return the number of the last person standing.
// People 1..n stand in a circle. Counting from person 1, every k-th person leaves, and
// counting continues with the next person.
//
// Example:
//   last_survivor(7, 3) is 4   // people leave in the order 3, 6, 2, 7, 5, 1
//   last_survivor(5, 2) is 3
//   last_survivor(1, 5) is 1   // one person is already the last one standing
//
// Use a std::queue: send people from the front to the back while you count.
int last_survivor(int n, int k) {
    throw "TODO";
}
