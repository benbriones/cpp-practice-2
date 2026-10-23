#include "grader.hpp"
#include "03c_even_more_references_pointers/05_reading_signatures.cpp"

TEST("trace_7: which calls can change x") {
    // (2) and (4) reach x directly, (6) assigns to it, and (7) can write through px
    CHECK_EQ(trace_7(), {2, 4, 6, 7});
}

TEST("find_account: points at the element") {
    std::vector<int> balances{100, 50};
    CHECK(find_account(balances, 0) == &balances[0], "should point at balances[0] itself");
    CHECK(find_account(balances, 1) == &balances[1], "should point at balances[1] itself");
}

TEST("find_account: nullptr out of range") {
    std::vector<int> balances{100, 50};
    CHECK_EQ(find_account(balances, 2), nullptr);
    CHECK_EQ(find_account(balances, 1000), nullptr);
    std::vector<int> empty;
    CHECK_EQ(find_account(empty, 0), nullptr);
}

TEST("find_account: writing through the result") {
    std::vector<int> balances{100, 50};
    *find_account(balances, 0) = 0;
    CHECK_EQ(balances, {0, 50});
}

TEST("withdraw: takes the money out") {
    int balance = 100;
    CHECK_EQ(withdraw(balance, 30), true);
    CHECK_EQ(balance, 70);
    CHECK_EQ(withdraw(balance, 70), true);
    CHECK_EQ(balance, 0);
}

TEST("withdraw: too much changes nothing") {
    int balance = 70;
    CHECK_EQ(withdraw(balance, 71), false);
    CHECK_EQ(balance, 70);
}

TEST("withdraw: amount must be positive") {
    int balance = 70;
    CHECK_EQ(withdraw(balance, 0), false);
    CHECK_EQ(withdraw(balance, -10), false);
    CHECK_EQ(balance, 70);
}

TEST("withdraw: a vector element") {
    std::vector<int> balances{100, 50};
    CHECK_EQ(withdraw(balances[1], 20), true);
    CHECK_EQ(balances, {100, 30});
}

TEST("transfer: moves the money") {
    std::vector<int> balances{100, 50};
    CHECK_EQ(transfer(balances, 0, 1, 30), true);
    CHECK_EQ(balances, {70, 80});
    CHECK_EQ(transfer(balances, 1, 0, 80), true);
    CHECK_EQ(balances, {150, 0});
}

TEST("transfer: not enough money changes nothing") {
    std::vector<int> balances{100, 50};
    CHECK_EQ(transfer(balances, 1, 0, 500), false);
    CHECK_EQ(transfer(balances, 1, 0, 0), false);
    CHECK_EQ(transfer(balances, 1, 0, -5), false);
    CHECK_EQ(balances, {100, 50});
}

TEST("transfer: a missing account changes nothing") {
    std::vector<int> balances{100, 50};
    CHECK(!transfer(balances, 0, 7, 10), "there is no account 7, so the transfer should fail");
    CHECK_EQ(balances, {100, 50});
    CHECK(!transfer(balances, 7, 0, 10), "there is no account 7, so the transfer should fail");
    CHECK_EQ(balances, {100, 50});
}

TEST("transfer: to the same account") {
    std::vector<int> balances{100, 50};
    CHECK_EQ(transfer(balances, 0, 0, 30), true);
    CHECK_EQ(balances, {100, 50});
    CHECK_EQ(transfer(balances, 1, 1, 60), false);
    CHECK_EQ(balances, {100, 50});
}

TEST("after_fee: takes the fee from each") {
    CHECK_EQ(after_fee({100, 20}, 5), {95, 15});
}

TEST("after_fee: never below 0") {
    CHECK_EQ(after_fee({100, 3, 0}, 5), {95, 0, 0});
    CHECK_EQ(after_fee({5}, 5), {0});
}

TEST("after_fee: no fee and no accounts") {
    CHECK_EQ(after_fee({7, 8}, 0), {7, 8});
    CHECK_EQ(after_fee({}, 5), {});
}

TEST("after_fee: the caller's balances are unchanged") {
    std::vector<int> balances{100, 3, 0};
    std::vector<int> preview = after_fee(balances, 5);
    CHECK_EQ(preview, {95, 0, 0});
    CHECK_EQ(balances, {100, 3, 0});
}
