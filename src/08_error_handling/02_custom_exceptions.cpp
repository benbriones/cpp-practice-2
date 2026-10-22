// === Lesson: Exception classes and hierarchies ===============================
//
// Your own exception class gives an error a name callers can catch, and room for
// extra data. Base it on a standard exception, usually std::runtime_error, which
// already stores the message and returns it from what():
//
//     class HttpError : public std::runtime_error {
//     public:
//         HttpError(int status, const std::string &message)
//             : std::runtime_error("HTTP " + std::to_string(status) + ": " + message),
//               status_(status) {}
//
//         int status() const { return status_; }
//
//     private:
//         int status_;
//     };
//
// `: public std::runtime_error` makes every HttpError also a std::runtime_error
// (inheritance gets its own module later). The member initializer list after the
// `:` in the constructor builds the base part with its message, then the class's
// own members. The base must be built there, not assigned in the body.
//
// When a class adds no data, `using Base::Base;` inherits the base's constructors
// so you don't have to write them:
//
//     class NotFound : public HttpError {
//     public:
//         using HttpError::HttpError;
//     };
//
// The classes form a family tree, and a catch clause matches its own type or any
// type derived from it. Clauses are tried top to bottom and the first match wins,
// so put the most specific first. (clang warns when a clause can never be reached.)
//
//     try {
//         fetch("/home");
//     } catch (const NotFound &) {               // just this one kind
//         show_404_page();
//     } catch (const HttpError &e) {            // any other HttpError
//         log("status " + std::to_string(e.status()));
//     } catch (const std::exception &e) {       // anything else from the std family
//         log(e.what());
//     }
//
// An exception that no clause matches keeps going up to the next try. A function
// that doesn't want to handle an error simply doesn't catch it, and it passes
// through. Inside a catch, a bare `throw;` rethrows the same exception.
//
// Read more: https://www.learncpp.com/cpp-tutorial/exceptions-classes-and-inheritance/
//            https://www.learncpp.com/cpp-tutorial/rethrowing-exceptions/
//
// === Exercise: Your own exception types ======================================
// Callers can catch exactly the errors they care about, or a base class to catch
// a whole family.
//
// ./grade 08_error_handling/02_custom_exceptions

#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Given. ConfigError *is a* std::runtime_error (the `: public` part; inheritance
// gets its own module) and reuses its constructors (the `using` line).
class ConfigError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Throw a MissingKey when a setting is missing.
// what() returns "missing key: <key>", and key() returns the key itself.
// Pass the message up to ConfigError in the member initializer list.
// Store the key in a member of your own.
//
// Example:
//   MissingKey error("port");
//   error.what() is "missing key: port"
//   error.key() is "port"
//
// A MissingKey is also a ConfigError, so catch (const ConfigError &) catches it too.
class MissingKey : public ConfigError {
public:
    explicit MissingKey(const std::string &key) : ConfigError("TODO") {
        throw "TODO";
    }

    const std::string &key() const {
        throw "TODO";
    }
};

// Split "key=value" at the first '=' and return {key, value}.
// The value may be empty or contain more '='s.
// Throw ConfigError("missing '=' in: <line>") if there's no '='.
// Throw ConfigError("empty key in: <line>") if nothing comes before the '='.
//
// Example:
//   parse_config_line("port=8080") is {"port", "8080"}
//   parse_config_line("debug=") is {"debug", ""}
//   parse_config_line("query=a=b") is {"query", "a=b"}
//   parse_config_line("oops") throws ConfigError("missing '=' in: oops")
//   parse_config_line("=5") throws ConfigError("empty key in: =5")
std::pair<std::string, std::string> parse_config_line(const std::string &line) {
    throw "TODO";
}

// Return all the lines parsed into a map of key to value.
// A later line overrides an earlier one with the same key.
// Skip empty lines and lines starting with '#'.
// Errors propagate: a bad line's ConfigError goes straight out to the caller.
//
// Example:
//   parse_config({"# settings", "host=localhost", "", "port=8080", "port=9000"})
//     is {{"host", "localhost"}, {"port", "9000"}}
//   parse_config({"a=1", "broken", "b=2"}) throws ConfigError
std::map<std::string, std::string> parse_config(const std::vector<std::string> &lines) {
    throw "TODO";
}

// Return the value stored for key in settings.
// Throw MissingKey(key) if key isn't there.
//
// Example:
//   settings = {{"host", "localhost"}}
//   get_setting(settings, "host") is "localhost"
//   get_setting(settings, "port") throws MissingKey, and its key() is "port"
std::string get_setting(const std::map<std::string, std::string> &settings,
                        const std::string &key) {
    throw "TODO";
}

// Run action and return a report of what happened:
//   no exception                → "ok"
//   MissingKey                  → "please set <key>"
//   any other ConfigError       → "config error: <what()>"
//   any other std::exception    → "error: <what()>"
//
// Example:
//   describe_failure([] {}) is "ok"
//   describe_failure([] { throw MissingKey("port"); }) is "please set port"
//   describe_failure([] { throw ConfigError("bad value"); }) is "config error: bad value"
//   describe_failure([] { throw std::out_of_range("too far"); }) is "error: too far"
//
// A catch clause also matches derived types, so the most specific clause goes first.
std::string describe_failure(const std::function<void()> &action) {
    throw "TODO";
}
