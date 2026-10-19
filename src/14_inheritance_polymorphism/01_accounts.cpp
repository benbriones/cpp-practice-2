// Exercise: Bank accounts
// A base class Account and two derived classes that change how withdraw works.
//
// `class Savings : public Account` inherits everything public. A derived
// constructor initialises its base first: Savings(...) : Account(balance) {}.
// A `virtual` function can be replaced in a derived class; mark the replacement
// `override`. Inside it, Account::withdraw(amount) still calls the base version.
//
// Grade: grade 14_inheritance_polymorphism/01_accounts

#include <stdexcept>
#include <vector>

class Account {
public:
    // A negative opening balance throws std::invalid_argument.
    explicit Account(double opening_balance = 0) {
        throw "TODO";
    }

    // Base classes used through references or pointers need a virtual destructor.
    virtual ~Account() = default;

    double balance() const {
        throw "TODO";
    }

    // Adds amount. A non-positive amount throws std::invalid_argument.
    void deposit(double amount) {
        throw "TODO";
    }

    // Takes amount out and returns true, or returns false and changes nothing if
    // the balance is too low. A non-positive amount throws std::invalid_argument.
    virtual bool withdraw(double amount) {
        throw "TODO";
    }

protected:
    // TODO: data members. Protected members are visible to derived classes.
};

class SavingsAccount : public Account {
public:
    // interest_rate is a fraction: 0.05 means 5%.
    SavingsAccount(double opening_balance, double interest_rate) {
        throw "TODO";
    }

    // Adds balance × interest_rate to the balance.
    void add_interest() {
        throw "TODO";
    }

    // Works like Account::withdraw, but only the first 3 successful withdrawals
    // are allowed; after that it returns false. Refused withdrawals don't count.
    bool withdraw(double amount) override {
        throw "TODO";
    }

private:
    // TODO: data members
};

class CheckingAccount : public Account {
public:
    // The balance may go negative, but never below -overdraft_limit.
    CheckingAccount(double opening_balance, double overdraft_limit) {
        throw "TODO";
    }

    // Same rules as Account::withdraw (true/false, bad amounts throw), except
    // the overdraft is allowed.
    bool withdraw(double amount) override {
        throw "TODO";
    }

private:
    // TODO: data members
};

// Withdraws amount from every account and returns how many withdrawals succeeded.
// Each account follows its own rules, even though you only see Account*.
int withdraw_from_all(const std::vector<Account*>& accounts, double amount) {
    throw "TODO";
}
