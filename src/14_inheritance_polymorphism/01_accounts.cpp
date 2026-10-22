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
    // Open an account holding opening_balance.
    // A negative opening balance throws std::invalid_argument; 0 is fine.
    //
    // Example:
    //   Account account(100);   // account.balance() is 100
    //   Account(-10) throws std::invalid_argument
    explicit Account(double opening_balance = 0) {
        throw "TODO";
    }

    // Base classes used through references or pointers need a virtual destructor.
    virtual ~Account() = default;

    double balance() const {
        throw "TODO";
    }

    // Add amount to the balance.
    // A non-positive amount throws std::invalid_argument and changes nothing.
    //
    // Example:
    //   Account account(100);
    //   account.deposit(50);   // balance is now 150
    //   account.deposit(0) and account.deposit(-5) throw std::invalid_argument
    void deposit(double amount) {
        throw "TODO";
    }

    // Take amount out of the balance and return true.
    // If the balance is too low, return false and change nothing.
    // A non-positive amount throws std::invalid_argument.
    //
    // Example:
    //   Account account(100);
    //   account.withdraw(100.01);   // false: balance stays 100
    //   account.withdraw(100);      // true: balance is now 0
    //   account.withdraw(-1) throws std::invalid_argument
    //
    // It's virtual, so derived classes can replace the rules.
    virtual bool withdraw(double amount) {
        throw "TODO";
    }

protected:
    // TODO: data members. Protected members are visible to derived classes.
};

class SavingsAccount : public Account {
public:
    // Open a savings account holding opening_balance.
    // interest_rate is a fraction: 0.05 means 5%.
    // Account's rules still apply, so a negative opening balance throws.
    //
    // Example:
    //   SavingsAccount savings(1000, 0.05);   // balance 1000, 5% interest
    //   SavingsAccount(-1, 0.01) throws std::invalid_argument
    SavingsAccount(double opening_balance, double interest_rate) {
        throw "TODO";
    }

    // Add balance × interest_rate to the balance.
    // Each call works on the current balance, so interest compounds.
    //
    // Example:
    //   SavingsAccount savings(1000, 0.05);
    //   savings.add_interest();   // balance is 1050
    //   savings.add_interest();   // balance is 1102.5
    void add_interest() {
        throw "TODO";
    }

    // Work like Account::withdraw, but allow only the first 3 successful withdrawals.
    // After that, return false. Refused withdrawals don't count toward the 3.
    //
    // Example:
    //   SavingsAccount savings(100, 0.01);
    //   savings.withdraw(500);   // false: balance too low, so it doesn't count
    //   savings.withdraw(10);    // true (1st)
    //   savings.withdraw(10);    // true (2nd)
    //   savings.withdraw(10);    // true (3rd): balance is now 70
    //   savings.withdraw(10);    // false: no withdrawals left
    bool withdraw(double amount) override {
        throw "TODO";
    }

private:
    // TODO: data members
};

class CheckingAccount : public Account {
public:
    // Open a checking account holding opening_balance.
    // The balance may go negative, but never below -overdraft_limit.
    //
    // Example:
    //   CheckingAccount checking(100, 50);   // balance 100, can drop as low as -50
    CheckingAccount(double opening_balance, double overdraft_limit) {
        throw "TODO";
    }

    // Same rules as Account::withdraw (true/false, bad amounts throw), except
    // the overdraft is allowed: refuse only if the balance would drop below -overdraft_limit.
    //
    // Example:
    //   CheckingAccount checking(100, 50);
    //   checking.withdraw(120);   // true: balance is -20
    //   checking.withdraw(40);    // false: -60 is below -50, so balance stays -20
    //   checking.withdraw(30);    // true: balance is -50, exactly the limit
    //   checking.withdraw(0) throws std::invalid_argument
    bool withdraw(double amount) override {
        throw "TODO";
    }

private:
    // TODO: data members
};

// Withdraw amount from every account and return how many withdrawals succeeded.
// Each account follows its own rules, even though you only see Account*.
// An empty list returns 0.
//
// Example:
//   plain is Account(50), savings is SavingsAccount(500, 0.01),
//   checking is CheckingAccount(50, 100)
//   withdraw_from_all({&plain, &savings, &checking}, 60) returns 2
//   // plain refuses and stays 50; savings drops to 440; checking drops to -10.
//
// withdraw is virtual, so each call runs the version for the account's real type.
int withdraw_from_all(const std::vector<Account*>& accounts, double amount) {
    throw "TODO";
}
