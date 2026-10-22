#include "grader.hpp"
#include "11_raii_smart_pointers/01_scope_guard.cpp"

TEST("ScopeGuard: runs its action at the end of the scope") {
    int calls = 0;
    {
        ScopeGuard guard([&] { ++calls; });
        CHECK_EQ(calls, 0);
    }
    CHECK_EQ(calls, 1);
}

TEST("ScopeGuard: runs when an exception leaves the scope") {
    int calls = 0;
    try {
        ScopeGuard guard([&] { ++calls; });
        throw std::runtime_error("boom");
    } catch (const std::runtime_error &) {
    }
    CHECK_EQ(calls, 1);
}

TEST("ScopeGuard: runs on an early return") {
    int calls = 0;
    auto finish_early = [&](bool early) {
        ScopeGuard guard([&] { ++calls; });
        if (early) return 1;
        return 2;
    };
    CHECK_EQ(finish_early(true), 1);
    CHECK_EQ(calls, 1);
}

TEST("ScopeGuard: dismiss() cancels the action") {
    int calls = 0;
    {
        ScopeGuard guard([&] { ++calls; });
        guard.dismiss();
    }
    CHECK_EQ(calls, 0);
}

TEST("ScopeGuard: guards run in reverse order of creation") {
    std::vector<int> order;
    {
        ScopeGuard first([&] { order.push_back(1); });
        ScopeGuard second([&] { order.push_back(2); });
    }
    CHECK_EQ(order, {2, 1});
}

TEST("with_logging: normal run") {
    std::vector<std::string> log;
    with_logging(log, [&] { log.push_back("working"); });
    CHECK_EQ(log, {"start", "working", "end"});
}

TEST("with_logging: still logs \"end\" when work throws") {
    std::vector<std::string> log;
    CHECK_THROWS(std::runtime_error, with_logging(log, [] { throw std::runtime_error("disk full"); }));
    CHECK_EQ(log, {"start", "end"});
}

TEST("apply_to_all: updates every balance") {
    std::vector<int> balances{10, 20, 30};
    apply_to_all(balances, -5);
    CHECK_EQ(balances, {5, 15, 25});
    apply_to_all(balances, 100);
    CHECK_EQ(balances, {105, 115, 125});
}

TEST("apply_to_all: rolls everything back on failure") {
    std::vector<int> balances{5, 1, 7};
    CHECK_THROWS(std::invalid_argument, apply_to_all(balances, -3));
    CHECK_EQ(balances, {5, 1, 7});
}

TEST("apply_to_all: a balance can reach exactly zero") {
    std::vector<int> balances{3, 4};
    apply_to_all(balances, -3);
    CHECK_EQ(balances, {0, 1});
}
