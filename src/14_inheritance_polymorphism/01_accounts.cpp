// === Lesson: Inheritance and virtual functions ===============================
//
// `class Manager : public Employee` makes Manager a kind of Employee: it gets
// Employee's members, and a Manager can be used wherever an Employee& or
// Employee* is expected.
//
//     class Employee {
//     public:
//         explicit Employee(double salary) : salary_(salary) {}
//         virtual ~Employee() = default;
//
//         virtual double bonus() const { return salary_ * 0.05; }
//
//     protected:
//         double salary_;   // derived classes can use it; outside code can't
//     };
//
//     class Manager : public Employee {
//     public:
//         Manager(double salary, int reports)
//             : Employee(salary), reports_(reports) {}   // base first, then members
//
//         double bonus() const override {
//             return Employee::bonus() + reports_ * 100;   // reuse the base version
//         }
//
//     private:
//         int reports_;
//     };
//
//     Manager boss(80'000, 4);
//     Employee& someone = boss;
//     someone.bonus();   // 4400: the Manager version, even through an Employee&
//
// A derived constructor can't set base members itself. It passes arguments to a
// base constructor in its initializer list, and the base part is built first.
//
// Only functions marked `virtual` dispatch on the object's real type. In Python
// or JavaScript every method works that way; in C++ a non-virtual function is
// picked at compile time from the declared type. `override` asks the compiler
// to check that you really are replacing a virtual function: a typo in the name
// or a missing const becomes an error instead of a silent new function.
//
// Base::function(...) calls the base version explicitly, which is how a derived
// version adds to the base behaviour instead of copying it.
//
// A class meant to be used through base pointers or references needs a virtual
// destructor, so destroying the object runs the derived destructor too.
//
// Read more: https://www.learncpp.com/cpp-tutorial/basic-inheritance-in-c/
//            https://www.learncpp.com/cpp-tutorial/virtual-functions/
//
// === Exercise: Bank accounts =================================================
// A base class Account and two derived classes that change how withdraw works.
//
// ./grade 14_inheritance_polymorphism/01_accounts

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
