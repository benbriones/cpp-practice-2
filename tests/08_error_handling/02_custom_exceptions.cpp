#include "grader.hpp"
#include "08_error_handling/02_custom_exceptions.cpp"

TEST("MissingKey: message and key") {
    MissingKey error("port");
    CHECK_EQ(std::string(error.what()), "missing key: port");
    CHECK_EQ(error.key(), "port");
}

TEST("MissingKey: can be caught as a ConfigError") {
    std::string caught_as_config_error = "(nothing caught)";
    try {
        throw MissingKey("host");
    } catch (const ConfigError& e) {
        caught_as_config_error = e.what();
    }
    CHECK_EQ(caught_as_config_error, "missing key: host");
}

TEST("parse_config_line: key and value") {
    CHECK_EQ(parse_config_line("port=8080"), {"port", "8080"});
    CHECK_EQ(parse_config_line("name=Ada Lovelace"), {"name", "Ada Lovelace"});
}

TEST("parse_config_line: empty value, or '=' inside the value") {
    CHECK_EQ(parse_config_line("debug="), {"debug", ""});
    CHECK_EQ(parse_config_line("query=a=b"), {"query", "a=b"});
}

TEST("parse_config_line: errors") {
    CHECK_THROWS(ConfigError, parse_config_line("no equals sign"));
    CHECK_THROWS(ConfigError, parse_config_line("=value"));
    std::string what_for_oops = "(nothing thrown)";
    try {
        parse_config_line("oops");
    } catch (const ConfigError& e) {
        what_for_oops = e.what();
    }
    CHECK_EQ(what_for_oops, "missing '=' in: oops");
    std::string what_for_equals_5 = "(nothing thrown)";
    try {
        parse_config_line("=5");
    } catch (const ConfigError& e) {
        what_for_equals_5 = e.what();
    }
    CHECK_EQ(what_for_equals_5, "empty key in: =5");
}

TEST("parse_config: builds a map") {
    std::map<std::string, std::string> expected{{"host", "localhost"}, {"port", "9000"}};
    CHECK_EQ(parse_config({"# settings", "host=localhost", "", "port=8080", "port=9000"}), expected);
    CHECK_EQ(parse_config({}), {});
}

TEST("parse_config: a bad line throws") {
    CHECK_THROWS(ConfigError, parse_config({"a=1", "broken", "b=2"}));
}

TEST("get_setting") {
    const std::map<std::string, std::string> settings{{"host", "localhost"}};
    CHECK_EQ(get_setting(settings, "host"), "localhost");
}

TEST("get_setting: missing key throws MissingKey") {
    const std::map<std::string, std::string> settings{{"host", "localhost"}};
    CHECK_THROWS(MissingKey, get_setting(settings, "port"));
    std::string key_of_thrown_error = "(nothing thrown)";
    try {
        get_setting(settings, "port");
    } catch (const MissingKey& e) {
        key_of_thrown_error = e.key();
    }
    CHECK_EQ(key_of_thrown_error, "port");
}

TEST("describe_failure: no exception") {
    CHECK_EQ(describe_failure([] {}), "ok");
}

TEST("describe_failure: MissingKey is caught first") {
    CHECK_EQ(describe_failure([] { throw MissingKey("port"); }), "please set port");
}

TEST("describe_failure: other config errors") {
    CHECK_EQ(describe_failure([] { throw ConfigError("bad value"); }), "config error: bad value");
    CHECK_EQ(describe_failure([] { parse_config_line("nope"); }), "config error: missing '=' in: nope");
}

TEST("describe_failure: any other std::exception") {
    CHECK_EQ(describe_failure([] { throw std::out_of_range("too far"); }), "error: too far");
    CHECK_EQ(describe_failure([] { (void)std::vector<int>{}.at(3); }).substr(0, 7), "error: ");
}
