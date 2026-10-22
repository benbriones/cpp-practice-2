// === Lesson: Interfaces and dependency injection =============================
//
// C++ has no `interface` keyword. An abstract class with only pure virtual
// functions (plus a virtual destructor) plays that role, like an interface in
// TypeScript or Java. Code written against it works with any class that
// implements it, including ones written later, such as stand-ins for tests.
//
// Dependency injection: instead of creating what it depends on, a class is
// handed it, usually through its constructor:
//
//     class Clock {                        // the interface
//     public:
//         virtual ~Clock() = default;
//         virtual int hour() const = 0;
//     };
//
//     class FixedClock : public Clock {    // a stand-in for tests
//     public:
//         explicit FixedClock(int hour) : hour_(hour) {}
//         int hour() const override { return hour_; }
//     private:
//         int hour_;
//     };
//
//     class Greeter {
//     public:
//         explicit Greeter(const Clock& clock) : clock_(clock) {}
//         std::string greet() const {
//             return clock_.hour() < 12 ? "Good morning" : "Hello";
//         }
//     private:
//         const Clock& clock_;   // uses the caller's clock; doesn't own or copy it
//     };
//
//     FixedClock nine_am(9);
//     Greeter greeter(nine_am);
//     greeter.greet();   // "Good morning"
//
// A reference member must be set in the constructor's initializer list (there's
// no empty reference to start from) and can never be re-pointed. The object it
// refers to has to outlive the class holding it. Streams can't be copied, so a
// class that writes to one holds a std::ostream& too.
//
// A class can implement an interface by forwarding each call to another object
// of the same interface, adding something on the way (the decorator pattern).
//
// std::string_view to std::string: the conversion is explicit, and C++20 has no
// + between them. std::string(view) converts, += and append() accept a view, and
// a std::vector<std::string> takes one through emplace_back(view).
//
// Read more: https://en.cppreference.com/w/cpp/language/abstract_class
//            https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists
//
// === Exercise: Interfaces and dependency injection ===========================
// Logger is an interface. Write three loggers, then an OrderService that logs
// through whichever Logger it is handed. That's dependency injection: the tests
// give it a MemoryLogger so they can read what it logged.
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

// A Logger that keeps every message, in order.
// messages() returns them all; it's empty before the first log().
//
// Example:
//   MemoryLogger logger;
//   logger.log("first");
//   logger.log("second");
//   // logger.messages() is {"first", "second"}
//
// The tests hand one to other code so they can read back what it logged.
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

// A Logger that writes each message to a stream, followed by '\n'.
// It keeps a reference to the stream it's given, since streams can't be copied.
//
// Example:
//   std::ostringstream out;
//   StreamLogger logger(out);
//   logger.log("hello");
//   logger.log("world");
//   // out.str() is "hello\nworld\n"
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

// A Logger that passes each message on to another logger with a prefix in front.
// It refers to `inner` but doesn't own it.
// inner can be any Logger, even another PrefixLogger.
//
// Example:
//   PrefixLogger("[db] ", inner).log("connected") makes inner log "[db] connected".
//
//   PrefixLogger inner("[inner] ", memory);
//   PrefixLogger outer("[outer] ", inner);
//   outer.log("message");   // memory gets "[inner] [outer] message"
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

    // Place an order for quantity of item, logging the result.
    // For a positive quantity: count the order, log "order #N: <quantity> x <item>"
    // (N counts accepted orders from 1), and return true.
    // Otherwise log "rejected: <quantity> x <item>" and return false.
    //
    // Example:
    //   service.place_order("apple", 0);   // false, logs "rejected: 0 x apple"
    //   service.place_order("fig", 5);     // true, logs "order #1: 5 x fig"
    //   service.place_order("tea", 2);     // true, logs "order #2: 2 x tea"
    //
    // It logs through whichever Logger it was handed, without knowing which kind.
    bool place_order(const std::string& item, int quantity) {
        throw "TODO";
    }

    // Return how many orders were accepted. Rejected orders don't count.
    //
    // Example:
    //   after place_order("apple", 0) and place_order("fig", 5), order_count() is 1
    int order_count() const {
        throw "TODO";
    }

private:
    // TODO: data members
};
