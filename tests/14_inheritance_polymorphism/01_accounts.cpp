#include "grader.hpp"
#include "14_inheritance_polymorphism/01_accounts.cpp"

TEST("Account: deposit and withdraw") {
    Account account(100);
    account.deposit(50);
    CHECK_NEAR(account.balance(), 150.0);
    CHECK_EQ(account.withdraw(30), true);
    CHECK_NEAR(account.balance(), 120.0);
}

TEST("Account: refuses to overdraw") {
    Account account(100);
    CHECK_EQ(account.withdraw(100.01), false);
    CHECK_NEAR(account.balance(), 100.0);
    CHECK_EQ(account.withdraw(100), true);
    CHECK_NEAR(account.balance(), 0.0);
}

TEST("Account: rejects bad amounts") {
    Account account(10);
    CHECK_THROWS(std::invalid_argument, account.deposit(0));
    CHECK_THROWS(std::invalid_argument, account.deposit(-5));
    CHECK_THROWS(std::invalid_argument, account.withdraw(-1));
    CHECK_THROWS(std::invalid_argument, Account(-10));
    CHECK_NEAR(account.balance(), 10.0);
}

TEST("SavingsAccount: add_interest") {
    SavingsAccount savings(1000, 0.05);
    savings.add_interest();
    CHECK_NEAR(savings.balance(), 1050.0);
    savings.add_interest();
    CHECK_NEAR(savings.balance(), 1102.5);
}

TEST("SavingsAccount: only three withdrawals") {
    SavingsAccount savings(1000, 0.01);
    CHECK_EQ(savings.withdraw(10), true);
    CHECK_EQ(savings.withdraw(10), true);
    CHECK_EQ(savings.withdraw(10), true);
    CHECK_EQ(savings.withdraw(10), false);
    CHECK_NEAR(savings.balance(), 970.0);
}

TEST("SavingsAccount: refused withdrawals don't use up the limit") {
    SavingsAccount savings(100, 0.01);
    CHECK_EQ(savings.withdraw(500), false);
    CHECK_EQ(savings.withdraw(500), false);
    CHECK_EQ(savings.withdraw(10), true);
    CHECK_EQ(savings.withdraw(10), true);
    CHECK_EQ(savings.withdraw(10), true);
    CHECK_NEAR(savings.balance(), 70.0);
}

TEST("SavingsAccount: base-class rules still apply") {
    SavingsAccount savings(50, 0.01);
    CHECK_THROWS(std::invalid_argument, savings.withdraw(-5));
    CHECK_THROWS(std::invalid_argument, savings.deposit(0));
    CHECK_THROWS(std::invalid_argument, SavingsAccount(-1, 0.01));
}

TEST("CheckingAccount: overdraft down to the limit") {
    CheckingAccount checking(100, 50);
    CHECK_EQ(checking.withdraw(120), true);
    CHECK_NEAR(checking.balance(), -20.0);
    CHECK_EQ(checking.withdraw(40), false);
    CHECK_NEAR(checking.balance(), -20.0);
    CHECK_EQ(checking.withdraw(30), true);
    CHECK_NEAR(checking.balance(), -50.0);
}

TEST("CheckingAccount: rejects bad amounts") {
    CheckingAccount checking(0, 100);
    CHECK_THROWS(std::invalid_argument, checking.withdraw(0));
    CHECK_NEAR(checking.balance(), 0.0);
}

TEST("Derived rules apply through an Account&") {
    CheckingAccount checking(100, 50);
    Account& as_base = checking;
    CHECK_EQ(as_base.withdraw(120), true);
    CHECK_NEAR(as_base.balance(), -20.0);

    SavingsAccount savings(1000, 0.01);
    Account& savings_as_base = savings;
    savings_as_base.withdraw(1);
    savings_as_base.withdraw(1);
    savings_as_base.withdraw(1);
    CHECK_EQ(savings_as_base.withdraw(1), false);
}

TEST("withdraw_from_all") {
    Account plain(50);
    SavingsAccount savings(500, 0.01);
    CheckingAccount checking(50, 100);
    std::vector<Account*> accounts{&plain, &savings, &checking};
    CHECK_EQ(withdraw_from_all(accounts, 60), 2);
    CHECK_NEAR(plain.balance(), 50.0);
    CHECK_NEAR(savings.balance(), 440.0);
    CHECK_NEAR(checking.balance(), -10.0);
    CHECK_EQ(withdraw_from_all({}, 10), 0);
}
