// Exercise: Your own exception types
// Deriving from a standard exception gives an error a name (and extra data).
// Callers can catch exactly the errors they care about, or a base class to catch
// a whole family. Catch clauses are tried top to bottom, so list the most
// specific type first.
//
// Grade: grade 08_error_handling/02_custom_exceptions

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

// Thrown when a setting is missing. what() returns "missing key: <key>", and key()
// returns the key itself. Pass the message up to ConfigError in the member
// initializer list, and store the key in a member of your own.
class MissingKey : public ConfigError {
public:
    explicit MissingKey(const std::string& key) : ConfigError("TODO") {
        throw "TODO";
    }

    const std::string& key() const {
        throw "TODO";
    }
};

// Split "key=value" at the first '='; the value may be empty or contain more '='s.
// Throws ConfigError("missing '=' in: <line>") if there's no '=',
// and ConfigError("empty key in: <line>") if nothing comes before it.
std::pair<std::string, std::string> parse_config_line(const std::string& line) {
    throw "TODO";
}

// All lines parsed into a map; a later line overrides an earlier one with the same
// key. Empty lines and lines starting with '#' are skipped. Errors propagate.
std::map<std::string, std::string> parse_config(const std::vector<std::string>& lines) {
    throw "TODO";
}

// The value for key; throws MissingKey(key) if it isn't there.
std::string get_setting(const std::map<std::string, std::string>& settings,
                        const std::string& key) {
    throw "TODO";
}

// Run action and report what happened:
//   no exception                → "ok"
//   MissingKey                  → "please set <key>"
//   any other ConfigError       → "config error: <what()>"
//   any other std::exception    → "error: <what()>"
std::string describe_failure(const std::function<void()>& action) {
    throw "TODO";
}
