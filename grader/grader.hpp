/** Goal: the tiny test framework every tests/<module>/<exercise>.cpp includes. */
// Usage: TEST("name") { CHECK_EQ(f(2), 4); }  ·  PROGRAM_TEST("name", { .input = ..., .output = ... });
#pragma once

#include <cxxabi.h>

#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

namespace grader {

// Thrown by a failed check; ends the current test.
struct Failure {
    std::string message;
};

// One run of the exercise's main(): stdin, command-line args, expected stdout and exit code.
struct ProgramTest {
    std::string input{};
    std::string output{};
    std::vector<std::string> args{};
    int exit_code = 0;
};

// A registered test: either a function body or a program run.
struct Entry {
    std::string name;
    void (*body)() = nullptr;
    std::optional<ProgramTest> program{};
};

inline std::vector<Entry> &registry() {
    static std::vector<Entry> entries;
    return entries;
}

inline bool add_test(const char *name, void (*body)()) {
    registry().push_back({name, body, std::nullopt});
    return true;
}

inline bool add_program_test(const char *name, ProgramTest test) {
    registry().push_back({name, nullptr, std::move(test)});
    return true;
}

[[noreturn]] inline void fail(std::string message) { throw Failure{std::move(message)}; }

// ---- Describing values in failure messages ----

inline std::string demangle(const char *mangled) {
    int status = 0;
    std::unique_ptr<char, void (*)(void *)> out(abi::__cxa_demangle(mangled, nullptr, nullptr, &status),
                                               std::free);
    std::string name = status == 0 ? out.get() : mangled;
    // libc++ hides std types in an inline namespace; drop it so messages read std::string.
    for (auto pos = name.find("::__1"); pos != std::string::npos; pos = name.find("::__1")) {
        name.erase(pos, 5);
    }
    return name;
}

template <class T>
std::string type_name() {
    return demangle(typeid(T).name());
}

inline std::string escape(std::string_view text) {
    std::string out;
    for (char c : text) {
        switch (c) {
            case '\n': out += "\\n"; break;
            case '\t': out += "\\t"; break;
            case '\r': out += "\\r"; break;
            case '\0': out += "\\0"; break;
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            default: out += c;
        }
    }
    return out;
}

inline std::string quote(std::string_view text) { return "\"" + escape(text) + "\""; }

template <class T>
struct is_optional : std::false_type {};
template <class T>
struct is_optional<std::optional<T>> : std::true_type {};

template <class T>
struct is_variant : std::false_type {};
template <class... T>
struct is_variant<std::variant<T...>> : std::true_type {};

template <class T>
concept Streamable = requires(std::ostream &os, const T &value) { os << value; };

template <class T>
concept Iterable = requires(const T &range) {
    std::begin(range);
    std::end(range);
};

template <class T>
concept TupleLike = requires { std::tuple_size<T>::value; };

template <class T>
concept SmartPointer = requires(const T &p) {
    { p.get() } -> std::convertible_to<const volatile void *>;
    typename T::element_type;
};

template <class T>
std::string describe(const T &value);

inline std::string describe_double(double value) {
    // Show 2.0 rather than 2 so doubles never look like ints; otherwise shortest round-trip form.
    if (std::isfinite(value) && value == std::floor(value) && std::fabs(value) < 1e15) {
        return std::format("{:.1f}", value);
    }
    return std::format("{}", value);
}

template <class T>
std::string describe(const T &value) {
    using std::begin, std::end;
    if constexpr (std::is_same_v<T, bool>) {
        return value ? "true" : "false";
    } else if constexpr (std::is_same_v<T, char>) {
        return "'" + escape(std::string_view(&value, 1)) + "'";
    } else if constexpr (std::is_same_v<T, std::nullptr_t>) {
        return "nullptr";
    } else if constexpr (std::is_same_v<T, std::filesystem::path>) {
        return quote(value.string());
    } else if constexpr (std::is_pointer_v<T>) {
        using Pointee = std::remove_cv_t<std::remove_pointer_t<T>>;
        if (value == nullptr) return "nullptr";
        if constexpr (std::is_same_v<Pointee, char>) {
            return quote(value);
        } else if constexpr (std::is_object_v<Pointee> && !std::is_void_v<Pointee>) {
            return "pointer to " + describe(*value);
        } else {
            return "a non-null pointer";
        }
    } else if constexpr (SmartPointer<T>) {
        if (!value) return "nullptr";
        return "owning pointer to " + describe(*value);
    } else if constexpr (std::is_convertible_v<const T &, std::string_view>) {
        return quote(std::string_view(value));
    } else if constexpr (std::is_enum_v<T>) {
        return type_name<T>() + "(" +
               std::to_string(static_cast<long long>(static_cast<std::underlying_type_t<T>>(value))) +
               ")";
    } else if constexpr (std::is_floating_point_v<T>) {
        return describe_double(static_cast<double>(value));
    } else if constexpr (std::is_integral_v<T>) {
        return std::to_string(value);
    } else if constexpr (is_optional<T>::value) {
        return value ? describe(*value) : "std::nullopt";
    } else if constexpr (is_variant<T>::value) {
        return std::visit([](const auto &alt) { return describe(alt); }, value);
    } else if constexpr (Iterable<T>) {
        std::string out = "{";
        std::size_t count = 0;
        for (auto it = begin(value); it != end(value); ++it, ++count) {
            if (count == 20) {
                out += ", ...";
                break;
            }
            if (count > 0) out += ", ";
            out += describe(*it);
        }
        return out + "}";
    } else if constexpr (TupleLike<T>) {
        std::string out = "{";
        std::apply(
            [&out](const auto &...parts) {
                std::size_t i = 0;
                ((out += (i++ ? ", " : "") + describe(parts)), ...);
            },
            value);
        return out + "}";
    } else if constexpr (Streamable<T>) {
        std::ostringstream os;
        os << value;
        return os.str();
    } else {
        return "(a " + type_name<T>() + ")";
    }
}

// ---- Checks ----

template <class T>
concept PlainInteger = std::integral<T> && !std::same_as<T, bool> && !std::same_as<T, char> &&
                       !std::same_as<T, wchar_t> && !std::same_as<T, char8_t> &&
                       !std::same_as<T, char16_t> && !std::same_as<T, char32_t>;

template <class T>
concept CharPointer = std::is_pointer_v<T> &&
                      std::is_same_v<std::remove_cv_t<std::remove_pointer_t<T>>, char>;

template <class A, class E>
bool equal(const A &actual, const E &expected) {
    if constexpr (PlainInteger<A> && PlainInteger<E>) {
        return std::cmp_equal(actual, expected);
    } else if constexpr (CharPointer<A> || CharPointer<E>) {
        // C-strings compare by content, not by address.
        if constexpr (CharPointer<A>) {
            if (actual == nullptr) return false;
        }
        if constexpr (CharPointer<E>) {
            if (expected == nullptr) return false;
        }
        return std::string_view(actual) == std::string_view(expected);
    } else {
        return actual == expected;
    }
}

// Splits "f(a, b), {1, 2}" at its first top-level comma to recover the actual-value expression.
inline std::string_view first_argument(std::string_view text) {
    int depth = 0;
    char quote_char = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        if (quote_char) {
            if (c == '\\') ++i;
            else if (c == quote_char) quote_char = 0;
        } else if (c == '"' || c == '\'') {
            quote_char = c;
        } else if (c == '(' || c == '[' || c == '{') {
            ++depth;
        } else if (c == ')' || c == ']' || c == '}') {
            --depth;
        } else if (c == ',' && depth == 0) {
            return text.substr(0, i);
        }
    }
    return text;
}

template <class A>
void check_eq(std::string_view text, const A &actual, const std::type_identity_t<A> &expected) {
    if (!equal(actual, expected)) {
        fail(std::string(first_argument(text)) + "\nExpected: " + describe(expected) +
             "\nReceived: " + describe(actual));
    }
}

template <class A, class E>
void check_near(std::string_view text, const A &actual, const E &expected, double tolerance = 1e-6) {
    double a = static_cast<double>(actual);
    double e = static_cast<double>(expected);
    if (!(std::fabs(a - e) <= tolerance)) {
        fail(std::string(first_argument(text)) + "\nExpected: " + describe_double(e) +
             " (within " + std::format("{}", tolerance) + ")\nReceived: " + describe_double(a));
    }
}

template <class C>
void check_true(std::string_view text, const C &condition, std::string_view message = {}) {
    if (!static_cast<bool>(condition)) {
        fail(message.empty() ? "Check failed: " + std::string(text) : std::string(message));
    }
}

template <class Ex, class F>
void check_throws(std::string_view text, F &&run) {
    std::string expected = "Expected: throws " + type_name<Ex>();
    try {
        run();
    } catch (const Ex &) {
        return;
    } catch (const char *) {
        throw;  // a TODO stub, reported as "not implemented"
    } catch (const std::exception &e) {
        fail(std::string(text) + "\n" + expected + "\nReceived: threw " + demangle(typeid(e).name()) +
             " (" + quote(e.what()) + ")");
    } catch (...) {
        fail(std::string(text) + "\n" + expected + "\nReceived: threw an unknown exception type");
    }
    fail(std::string(text) + "\n" + expected + "\nReceived: no exception");
}

// ---- Helpers for tests ----

// Runs `body` and returns everything it wrote to std::cout.
template <class F>
std::string capture_stdout(F &&body) {
    std::ostringstream captured;
    std::streambuf *original = std::cout.rdbuf(captured.rdbuf());
    try {
        body();
    } catch (...) {
        std::cout.rdbuf(original);
        throw;
    }
    std::cout.rdbuf(original);
    return captured.str();
}

// Each test runs in its own empty temp directory, so relative paths are safe to use.
inline void write_file(const std::string &path, std::string_view content) {
    std::ofstream(path, std::ios::binary) << content;
}

inline std::string read_file(const std::string &path) {
    std::ifstream in(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

}  // namespace grader

#define GRADER_CAT2(a, b) a##b
#define GRADER_CAT(a, b) GRADER_CAT2(a, b)

#define TEST(name)                                                                      \
    static void GRADER_CAT(grader_test_, __LINE__)();                                   \
    [[maybe_unused]] static const bool GRADER_CAT(grader_registered_, __LINE__) =       \
        ::grader::add_test(name, &GRADER_CAT(grader_test_, __LINE__));                  \
    static void GRADER_CAT(grader_test_, __LINE__)()

#define PROGRAM_TEST(name, ...)                                                   \
    [[maybe_unused]] static const bool GRADER_CAT(grader_registered_, __LINE__) = \
        ::grader::add_program_test(name, ::grader::ProgramTest __VA_ARGS__)

// CHECK(condition) or CHECK(condition, "message shown on failure")
#define CHECK(...) ::grader::check_true(#__VA_ARGS__, __VA_ARGS__)

// CHECK_EQ(actual, expected): expected converts to actual's type, so {1, 2, 3} works for a vector.
#define CHECK_EQ(...) ::grader::check_eq(#__VA_ARGS__, __VA_ARGS__)

// CHECK_NEAR(actual, expected) or CHECK_NEAR(actual, expected, tolerance)
#define CHECK_NEAR(...) ::grader::check_near(#__VA_ARGS__, __VA_ARGS__)

// CHECK_THROWS(ExceptionType, expression)
#define CHECK_THROWS(Type, ...) \
    ::grader::check_throws<Type>(#__VA_ARGS__, [&] { (void)(__VA_ARGS__); })
