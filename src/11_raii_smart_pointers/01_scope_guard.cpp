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
