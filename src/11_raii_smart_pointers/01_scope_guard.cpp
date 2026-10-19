// Exercise: Scope guard
// RAII: an object takes on a job in its constructor and finishes it in its
// destructor, and C++ runs the destructor however the scope ends: reaching the
// closing brace, an early return, or an exception. Build a ScopeGuard that runs
// an action when it goes out of scope, then use it in two functions.
//
// You never call a destructor yourself. Destructors must not throw, so that
// stub is an empty body instead of `throw "TODO";`.
//
// ./grade 11_raii_smart_pointers/01_scope_guard

#include <functional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class ScopeGuard {
public:
    // Remember the action; it runs later, when the guard is destroyed.
    explicit ScopeGuard(std::function<void()> action) {
        throw "TODO";
    }

    // Run the action, unless dismiss() was called.
    ~ScopeGuard() {
        // TODO
    }

    // Cancel the guard: the action will not run.
    void dismiss() {
        throw "TODO";
    }

    // Copying a guard would run its action twice, so copying is switched off.
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

private:
    // TODO: the data members you need
};

// Append "start" to log, run work(), then append "end" — even when work()
// throws. The exception must still reach the caller. Use a ScopeGuard.
void with_logging(std::vector<std::string>& log, const std::function<void()>& work) {
    throw "TODO";
}

// Add amount to every balance, in order. If any balance would drop below zero,
// throw std::invalid_argument and leave ALL balances exactly as they were.
// Save a copy, guard a rollback, and dismiss the guard once everything worked.
void apply_to_all(std::vector<int>& balances, int amount) {
    throw "TODO";
}
