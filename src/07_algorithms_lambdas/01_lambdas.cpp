// === Lesson: Lambdas and closures ============================================
//
// A lambda is a function written as an expression, right where you need it:
//
//     auto add = [](int a, int b) { return a + b; };
//     add(2, 3);                                         // 5
//
// The [ ] is the capture list: which local variables the body may use, and how.
//
//     int limit = 10;
//     auto too_big = [limit](int x) { return x > limit; };   // copies limit now
//     auto grow    = [&limit] { limit *= 2; };               // refers to limit itself
//     grow();                       // limit is 20, but too_big still compares with 10
//
// [=] captures everything the body uses by copy, [&] everything by reference.
//
// Unlike a JavaScript or Python closure, a by-reference capture doesn't keep the
// variable alive. Return a lambda that refers to a local, and it refers to a dead
// object (the sanitizer reports stack-use-after-return):
//
//     auto make_greeter() {
//         std::string name = "Ada";
//         return [&name] { return "hi " + name; };   // name dies when this returns
//     }
//
// So a lambda that outlives the current function should capture by copy.
//
// Captured copies are read-only inside the body unless you add `mutable`. An
// init capture, [name = expression], creates a variable that lives inside the
// lambda and keeps its value from one call to the next:
//
//     auto change = [last = 0](int x) mutable {
//         int d = x - last;
//         last = x;
//         return d;
//     };
//     change(5);                    // 5
//     change(8);                    // 3
//
// Every lambda has its own unnamed type, so use auto for local ones. To store,
// pass or return "any callable with this signature", use std::function from
// <functional>. It holds a copy of the lambda, captures included:
//
//     std::function<bool(int)> check = too_big;      // plain functions work too
//     check(12);                                     // true
//
// A function pointer, like int (*)(int, int), is the older C-style way to pass a
// function. Only a lambda that captures nothing converts to one:
//
//     int (*op)(int, int) = add;                     // fine: add captures nothing
//
// When a call returns a function, you can call the result straight away: f(1)(2).
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/
//            https://www.learncpp.com/cpp-tutorial/lambda-captures/
//
// === Exercise: Lambdas =======================================================
// Functions you create on the fly, store in variables, pass around, and return.
//
// ./grade 07_algorithms_lambdas/01_lambdas

#include <functional>
#include <vector>

// Return a function that multiplies its argument by factor.
// Each returned function keeps its own factor.
//
// Example:
//   auto triple = make_multiplier(3);
//   triple(5) is 15, triple(-2) is -6
//   make_multiplier(10)(7) is 70
//
// The returned function outlives this call, so it needs its own copy of factor.
std::function<int(int)> make_multiplier(int factor) {
    throw "TODO";
}

// Return a function that gives the next number each time it's called.
// The first call returns 1, then 2, then 3, and so on.
// Two counters made by separate calls count independently.
//
// Example:
//   auto first = make_counter();
//   auto second = make_counter();
//   first();    // 1
//   first();    // 2
//   second();   // 1, not 3
//   first();    // 3
//
// The count lives inside the returned function and carries over between calls.
std::function<int()> make_counter() {
    throw "TODO";
}

// Return the result of applying f to x, n times in a row.
// apply_n_times(f, 3, x) is f(f(f(x))).
// If n is 0, return x unchanged.
//
// Example:
//   auto add_three = [](int x) { return x + 3; };
//   apply_n_times(add_three, 4, 0) is 12   // 0 -> 3 -> 6 -> 9 -> 12
//   apply_n_times(add_three, 0, 7) is 7
int apply_n_times(const std::function<int(int)>& f, int n, int x) {
    throw "TODO";
}

// Return a function that applies g first, then f.
// compose(f, g)(x) is f(g(x)).
//
// Example:
//   auto add_one = [](int x) { return x + 1; };
//   auto double_it = [](int x) { return x * 2; };
//   compose(add_one, double_it)(5) is 11   // double first: 10, then add one
//   compose(double_it, add_one)(5) is 12   // add one first: 6, then double
//
// Order matters: the second argument runs first.
std::function<int(int)> compose(std::function<int(int)> f, std::function<int(int)> g) {
    throw "TODO";
}

// Return how many values make predicate return true.
// An empty vector gives 0.
//
// Example:
//   values = {5, 12, 7, 20, 3, 15}
//   count_where(values, [](int x) { return x > 10; }) is 3
//   count_where(values, [](int x) { return x % 2 == 1; }) is 4
int count_where(const std::vector<int>& values, const std::function<bool(int)>& predicate) {
    throw "TODO";
}

// Combine values left to right with op, starting from initial.
// fold({1, 2, 3}, 0, op) is op(op(op(0, 1), 2), 3).
// If values is empty, return initial.
//
// Example:
//   fold({1, 2, 3, 4}, 0, [](int a, int b) { return a + b; }) is 10
//   int subtract(int a, int b) { return a - b; }
//   fold({1, 2, 3}, 10, subtract) is 4   // ((10 - 1) - 2) - 3
//
// `int (*op)(int, int)` is a plain function pointer, the older C-style way to pass
// a function. A lambda with no captures converts to one automatically.
int fold(const std::vector<int>& values, int initial, int (*op)(int, int)) {
    throw "TODO";
}
