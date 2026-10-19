// Exercise: Interfaces and dependency injection
// Logger is an interface: an abstract class with only pure virtual functions.
// Write three loggers, then an OrderService that logs through whichever Logger
// it is handed. That's dependency injection: the tests give it a MemoryLogger
// so they can read what it logged.
//
// A class can hold a reference member (Logger& logger_;). It must be set in
// the constructor's initializer list and can't be re-pointed later.
//
// ./grade 14_inheritance_polymorphism/04_interfaces

#include <ostream>
#include <string>
#include <string_view>
#include <vector>

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(std::string_view message) = 0;
};

// Keeps every message, in order.
class MemoryLogger : public Logger {
public:
    void log(std::string_view message) override {
        throw "TODO";
    }

    const std::vector<std::string>& messages() const {
        throw "TODO";
    }

private:
    // TODO: data members
};

// Writes each message to a stream, followed by '\n'.
class StreamLogger : public Logger {
public:
    explicit StreamLogger(std::ostream& out) {
        throw "TODO";
    }

    void log(std::string_view message) override {
        throw "TODO";
    }

private:
    // TODO: data members
};

// Passes each message on to another logger with a prefix in front:
// PrefixLogger("[db] ", inner).log("connected") makes inner log "[db] connected".
// It refers to `inner` but doesn't own it.
class PrefixLogger : public Logger {
public:
    PrefixLogger(std::string prefix, Logger& inner) {
        throw "TODO";
    }

    void log(std::string_view message) override {
        throw "TODO";
    }

private:
    // TODO: data members
};

class OrderService {
public:
    explicit OrderService(Logger& logger) {
        throw "TODO";
    }

    // For a positive quantity: count the order, log "order #N: <quantity> x <item>"
    // (N counts accepted orders from 1), and return true.
    // Otherwise log "rejected: <quantity> x <item>" and return false.
    bool place_order(const std::string& item, int quantity) {
        throw "TODO";
    }

    // How many orders were accepted.
    int order_count() const {
        throw "TODO";
    }

private:
    // TODO: data members
};
