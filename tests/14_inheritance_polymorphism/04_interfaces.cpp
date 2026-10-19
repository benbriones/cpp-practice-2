#include "grader.hpp"
#include "14_inheritance_polymorphism/04_interfaces.cpp"

// Any class implementing Logger works with OrderService, including this one.
struct CountingLogger : Logger {
    int calls = 0;
    void log(std::string_view) override { ++calls; }
};

TEST("MemoryLogger: starts empty") {
    const MemoryLogger logger;
    CHECK_EQ(logger.messages(), {});
}

TEST("MemoryLogger: keeps messages in order") {
    MemoryLogger logger;
    logger.log("first");
    logger.log("second");
    logger.log("");
    CHECK_EQ(logger.messages(), {"first", "second", ""});
}

TEST("MemoryLogger: works through a Logger&") {
    MemoryLogger memory;
    Logger& logger = memory;
    logger.log("via the interface");
    CHECK_EQ(memory.messages(), {"via the interface"});
}

TEST("StreamLogger: one line per message") {
    std::ostringstream out;
    StreamLogger logger(out);
    logger.log("hello");
    logger.log("world");
    CHECK_EQ(out.str(), "hello\nworld\n");
}

TEST("PrefixLogger: adds the prefix") {
    MemoryLogger inner;
    PrefixLogger logger("[db] ", inner);
    logger.log("connected");
    logger.log("query took 3ms");
    CHECK_EQ(inner.messages(), {"[db] connected", "[db] query took 3ms"});
}

TEST("PrefixLogger: can wrap another PrefixLogger") {
    MemoryLogger memory;
    PrefixLogger inner("[inner] ", memory);
    PrefixLogger outer("[outer] ", inner);
    outer.log("message");
    // outer adds its prefix, then hands the result to inner, which adds its own in front.
    CHECK_EQ(memory.messages(), {"[inner] [outer] message"});
}

TEST("PrefixLogger: can wrap a StreamLogger") {
    std::ostringstream out;
    StreamLogger stream(out);
    PrefixLogger logger("> ", stream);
    logger.log("ok");
    CHECK_EQ(out.str(), "> ok\n");
}

TEST("OrderService: numbers the orders it accepts") {
    MemoryLogger logger;
    OrderService service(logger);
    CHECK_EQ(service.place_order("apple", 3), true);
    CHECK_EQ(service.place_order("pear", 1), true);
    CHECK_EQ(service.order_count(), 2);
    CHECK_EQ(logger.messages(), {"order #1: 3 x apple", "order #2: 1 x pear"});
}

TEST("OrderService: rejects quantities that aren't positive") {
    MemoryLogger logger;
    OrderService service(logger);
    CHECK_EQ(service.place_order("apple", 0), false);
    CHECK_EQ(service.place_order("kiwi", -2), false);
    CHECK_EQ(service.place_order("fig", 5), true);
    CHECK_EQ(service.order_count(), 1);
    CHECK_EQ(logger.messages(), {"rejected: 0 x apple", "rejected: -2 x kiwi", "order #1: 5 x fig"});
}

TEST("OrderService: works with any Logger") {
    CountingLogger counter;
    OrderService service(counter);
    service.place_order("a", 1);
    service.place_order("b", 0);
    CHECK_EQ(counter.calls, 2);
}

TEST("OrderService: logs through a PrefixLogger") {
    MemoryLogger memory;
    PrefixLogger shop("[shop] ", memory);
    OrderService service(shop);
    service.place_order("tea", 2);
    CHECK_EQ(memory.messages(), {"[shop] order #1: 2 x tea"});
}
