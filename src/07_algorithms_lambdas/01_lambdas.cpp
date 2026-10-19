// Exercise: Lambdas
// Functions you create on the fly, store in variables, pass around, and return.
//
// [capture](params) { body }: [x] copies x into the lambda, [&x] refers to the
// original. std::function<int(int)> (from <functional>) holds any callable that
// takes an int and returns an int. A lambda that changes its own copies needs
// `mutable` after the parameter list.
//
// ./grade 07_algorithms_lambdas/01_lambdas

#include <functional>
#include <vector>

// A function that multiplies its argument by factor: make_multiplier(3)(5) == 15.
std::function<int(int)> make_multiplier(int factor) {
    throw "TODO";
}

// Each call of the returned function gives the next number: 1, 2, 3, ...
// Two counters made by separate calls count independently.
std::function<int()> make_counter() {
    throw "TODO";
}

// f applied n times: apply_n_times(f, 3, x) == f(f(f(x))). n == 0 gives x back.
int apply_n_times(const std::function<int(int)>& f, int n, int x) {
    throw "TODO";
}

// A function that applies g first, then f: compose(f, g)(x) == f(g(x)).
std::function<int(int)> compose(std::function<int(int)> f, std::function<int(int)> g) {
    throw "TODO";
}

// How many values make predicate return true.
int count_where(const std::vector<int>& values, const std::function<bool(int)>& predicate) {
    throw "TODO";
}

// Combine values left to right, starting from initial:
// fold({1, 2, 3}, 0, op) == op(op(op(0, 1), 2), 3).
// `int (*op)(int, int)` is a plain function pointer, the older C-style way to pass
// a function. A lambda with no captures converts to one automatically.
int fold(const std::vector<int>& values, int initial, int (*op)(int, int)) {
    throw "TODO";
}
