// === Lesson: Destructors and RAII ============================================
//
// A destructor, ~ClassName(), runs automatically when an object's lifetime ends.
// For a local variable that's when its scope is left, however that happens: the
// closing brace, a return, a break, or an exception passing through. Locals are
// destroyed in reverse order of construction. You never call a destructor yourself.
//
// RAII ("resource acquisition is initialization") builds on that: a class takes
// on a job in its constructor and finishes it in its destructor, so the second
// half can't be forgotten. The standard library is full of it: std::vector frees
// its memory, std::ofstream closes its file, std::lock_guard unlocks its mutex.
//
//     int depth = 0;
//
//     class Indent {                 // one level deeper for as long as it lives
//     public:
//         Indent() { ++depth; }
//         ~Indent() { --depth; }
//     };
//
//     void walk(const Folder& folder) {
//         Indent indent;
//         print_name(folder.name);                // indented by depth
//         if (folder.subfolders.empty()) return;  // depth goes back down here...
//         for (const Folder& sub : folder.subfolders) walk(sub);
//     }                                           // ...and here, or if anything throws
//
// C++ has no `finally`. Where Python uses `with` and JavaScript uses try/finally,
// C++ uses an object whose destructor does the cleanup. The exception isn't
// caught or stopped: it keeps travelling to the caller while the destructors run.
// (If you do catch one, a bare `throw;` inside the catch block rethrows it.)
//
// To hold "something to run later", std::function<void()> from <functional>
// stores any callable that takes no arguments and returns nothing, like a lambda:
//
//     std::function<void()> on_exit = [&] { std::cout << "bye\n"; };
//     on_exit();                       // calls the lambda
//
// Destructors must not throw. They're noexcept by default, and an exception
// escaping one ends the program through std::terminate.
//
// Read more: https://www.learncpp.com/cpp-tutorial/destructors/
//            https://www.learncpp.com/cpp-tutorial/function-pointers/
//
// === Exercise: Scope guard ===================================================
// Build a ScopeGuard that runs an action when it goes out of scope, then use it
// in two functions. The destructor's stub is an empty body instead of
// `throw "TODO";`, since destructors must not throw.
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
    // Constructing the guard doesn't run the action.
    //
    // Example:
    //   int calls = 0;
    //   {
    //       ScopeGuard guard([&] { ++calls; });
    //       // calls is still 0 here
    //   }
    //   // the guard died at the brace, so calls is now 1
    explicit ScopeGuard(std::function<void()> action) {
        throw "TODO";
    }

    // Run the action, unless dismiss() was called.
    // It runs however the scope is left: the closing brace, a return, or an exception.
    //
    // Example:
    //   {
    //       ScopeGuard first([&] { order.push_back(1); });
    //       ScopeGuard second([&] { order.push_back(2); });
    //   }
    //   // order is now {2, 1}
    //
    // Locals are destroyed in reverse order, so the newest guard runs first.
    ~ScopeGuard() {
        // TODO
    }

    // Cancel the guard: the action will not run.
    //
    // Example:
    //   {
    //       ScopeGuard guard([&] { ++calls; });
    //       guard.dismiss();
    //   }
    //   // calls is unchanged
    void dismiss() {
        throw "TODO";
    }

    // Copying a guard would run its action twice, so copying is switched off.
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

private:
    // TODO: the data members you need
};

// Append "start" to log, run work(), then append "end".
// Append "end" even when work() throws. The exception must still reach the caller.
// Use a ScopeGuard.
//
// Example:
//   std::vector<std::string> log;
//   with_logging(log, [&] { log.push_back("working"); });
//   // log is {"start", "working", "end"}
//
//   std::vector<std::string> other;
//   with_logging(other, [] { throw std::runtime_error("disk full"); });
//   // throws std::runtime_error, and other is {"start", "end"}
void with_logging(std::vector<std::string>& log, const std::function<void()>& work) {
    throw "TODO";
}

// Add amount to every balance, in order.
// If any balance would drop below zero, throw std::invalid_argument and leave
// ALL balances exactly as they were, including ones already updated.
// A balance may reach exactly 0.
//
// Example:
//   balances = {10, 20, 30}
//   apply_to_all(balances, -5);   // balances is now {5, 15, 25}
//
//   balances = {5, 1, 7}
//   apply_to_all(balances, -3);   // throws: 1 - 3 is below zero; balances is still {5, 1, 7}
//
// Save a copy, guard a rollback, and dismiss the guard once everything worked.
void apply_to_all(std::vector<int>& balances, int amount) {
    throw "TODO";
}
