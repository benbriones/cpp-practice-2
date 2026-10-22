/** Goal: test dispatch for exercise binaries, driven by grade.py through environment variables. */
// Linked last, so its static initializer runs after every TEST has registered itself.

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "grader.hpp"

namespace {

// Exit code + stderr message grade.py reads as "the program hit a TODO".
constexpr int kTodoExitCode = 77;

[[noreturn]] void finish(const char *out_path, const std::string &result) {
    std::cout.flush();
    std::fflush(nullptr);
    std::ofstream(out_path) << result;
    std::_Exit(0);
}

// One line per test: kind, name, then program fields; tabs and newlines escaped.
void write_listing(const char *out_path) {
    std::string listing;
    for (const auto &entry : grader::registry()) {
        if (!entry.program) {
            listing += "U\t" + grader::escape(entry.name) + "\n";
            continue;
        }
        const auto &p = *entry.program;
        std::string args;
        for (const auto &arg : p.args) args += (args.empty() ? "" : "\x1f") + grader::escape(arg);
        listing += "P\t" + grader::escape(entry.name) + "\t" + grader::escape(p.input) + "\t" +
                   grader::escape(p.output) + "\t" + args + "\t" + std::to_string(p.exit_code) + "\n";
    }
    finish(out_path, listing);
}

void run_test(const char *out_path, std::size_t index) {
    const auto &entries = grader::registry();
    if (index >= entries.size() || entries[index].body == nullptr) {
        finish(out_path, "FAIL\nInternal grader error: no unit test #" + std::to_string(index));
    }
    try {
        entries[index].body();
    } catch (const grader::Failure &failure) {
        finish(out_path, "FAIL\n" + failure.message);
    } catch (const char *text) {
        if (std::string(text) == "TODO") finish(out_path, "TODO\n");
        finish(out_path, "FAIL\nYour code threw a string: " + grader::quote(text));
    } catch (const std::exception &e) {
        finish(out_path, "FAIL\nUnexpected exception " + grader::demangle(typeid(e).name()) + ": " +
                             grader::quote(e.what()));
    } catch (...) {
        finish(out_path, "FAIL\nUnexpected exception of an unknown type");
    }
    finish(out_path, "PASS\n");
}

// Set while running a unit test, so a TODO escaping a std::thread still reports as TODO.
const char *test_out_path = nullptr;

// An uncaught `throw "TODO"` (from main(), or from a thread in a test) means "not implemented yet".
[[noreturn]] void on_terminate() {
    if (auto current = std::current_exception()) {
        try {
            std::rethrow_exception(current);
        } catch (const char *text) {
            std::cout.flush();
            if (std::string(text) == "TODO" && test_out_path != nullptr) {
                finish(test_out_path, "TODO\n");
            }
            if (std::string(text) == "TODO") {
                std::fputs("\n[grade] reached a `throw \"TODO\"`: part of this exercise isn't written yet.\n", stderr);
                std::_Exit(kTodoExitCode);
            }
            std::fprintf(stderr, "\nUnhandled exception: a string \"%s\"\n", text);
        } catch (const std::exception &e) {
            std::cout.flush();
            std::fprintf(stderr, "\nUnhandled exception %s: \"%s\"\n",
                         grader::demangle(typeid(e).name()).c_str(), e.what());
        } catch (...) {
            std::fputs("\nUnhandled exception of an unknown type\n", stderr);
        }
    }
    std::abort();
}

[[maybe_unused]] const bool dispatched = [] {
    const char *out_path = std::getenv("GRADER_OUT");
    const char *mode = std::getenv("GRADER_MODE");
    if (out_path == nullptr || mode == nullptr) {
        std::set_terminate(on_terminate);
        return false;
    }
    if (std::string(mode) == "list") write_listing(out_path);
    const char *index = std::getenv("GRADER_INDEX");
    test_out_path = out_path;
    std::set_terminate(on_terminate);
    run_test(out_path, index ? std::strtoul(index, nullptr, 10) : 0);
    return true;
}();

}  // namespace

// Used only when the exercise defines no main() of its own.
__attribute__((weak)) int main() {
    std::fputs(
        "This exercise has no main(); it's graded through its functions.\n"
        "Add `int main() { ... }` to the file if you want to experiment.\n",
        stderr);
    return 0;
}
