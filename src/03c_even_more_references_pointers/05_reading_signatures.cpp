// === Lesson: Reading a signature =============================================
//
// A function's parameter list tells the caller what it may do with their data,
// before they read a line of its body. Learn to read it at a glance:
//
//     void f(int n);                gets a copy: your int is safe
//     void f(int &n);               may change your int
//     void f(const int &n);         reads your int without copying it, and won't change it
//     void f(int *p);               may change *p. Accepts nullptr only if its comment says so
//     void f(const int *p);         reads *p, and won't change it
//     void f(int *&p);              may re-point your pointer, or write through it
//     void f(int **pp);             the same, with &p at the call site
//
// The return type tells them what they get back:
//
//     int f();                                   a new value of their own
//     int &f(std::vector<int> &v);               a box inside v: f(v) = 0 writes v
//     const int &f(const std::vector<int> &v);   a box inside v, read-only
//     int *f(std::vector<int> &v);               a box inside v, or nullptr for "none"
//
// Choosing a parameter. Start from what the function does with each input:
//
//     reads a small value (int, char, double, a pointer)     by value
//     reads a big value (std::string, std::vector)           const&
//     changes the caller's variable                          &
//     takes an input or output the caller may leave out      pointer, nullptr when absent
//     needs a copy to change and return                      by value, then return it
//
// Functions built from smaller ones pass their references along. No copy is made
// at any step, so the innermost function changes the caller's box:
//
//     void add_point(int &score) { ++score; }
//
//     void award(std::vector<int> &scores, std::size_t winner) {
//         if (winner < scores.size()) add_point(scores[winner]);   // the element itself
//     }
//
//     award(scores, 2);         // scores[2] goes up by 1
//
// One copy anywhere in that chain cuts it. If award took std::vector<int> scores,
// add_point would bump an element of award's copy, and the caller would see
// nothing.
//
// Read more: https://www.learncpp.com/cpp-tutorial/in-and-out-parameters/
//            https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
//
// === Exercise: Reading a signature ===========================================
// Answer the trace, then implement four functions that manage bank balances,
// stored as a std::vector<int> where balances[i] is account i's balance. Each
// signature says what the function may do to the caller's data. Build transfer
// from the two functions before it.
//
// ./grade 03c_even_more_references_pointers/05_reading_signatures

#include <cstddef>
#include <vector>

// Trace 7. Which of these calls can change x? Return their numbers in order, like {2, 4}.
// Assume no casts, and that each function does anything its signature allows.
//
//     void f1(int n);
//     void f2(int &n);
//     void f3(const int &n);
//     void f4(int *p);
//     void f5(const int *p);
//     int f6(int n);
//     void f7(int *&p);
//
//     int x = 5;
//     int *px = &x;
//
//     (1) f1(x)    (2) f2(x)    (3) f3(x)    (4) f4(&x)
//     (5) f5(&x)   (6) x = f6(x)             (7) f7(px)
std::vector<int> trace_7() { throw "TODO"; }

// Return a pointer to balances[index], or nullptr when index is out of range.
//
// Example:
//   balances = {100, 50}
//   find_account(balances, 1) == &balances[1]
//   find_account(balances, 2) is nullptr
//   *find_account(balances, 0) = 0;   // balances is now {0, 50}
//
// Returns a pointer because the answer may be "no such account".
int *find_account(std::vector<int> &balances, std::size_t index) {
    if (index >= balances.size()) return nullptr;

    return &balances[index];
}

// Take amount out of balance and return true.
// If amount isn't positive, or is more than balance, return false and leave balance alone.
// A withdrawal may leave the balance at exactly 0.
//
// Example:
//   int balance = 100;
//   withdraw(balance, 30)    // returns true, balance is now 70
//   withdraw(balance, 80)    // returns false, balance is still 70
//   withdraw(balance, 0)     // returns false
//
// balance is a reference, so withdraw(balances[i], 30) changes the element itself.
bool withdraw(int &balance, int amount) {
    if (amount > balance || amount <= 0) return false;

    balance -= amount;
    return true;
}

// Move amount from account from to account to, and return true.
// Return false and change nothing when either index is out of range or the withdrawal fails.
// from and to may be the same account: if the withdrawal works, the money goes straight back.
//
// Example:
//   balances = {100, 50}
//   transfer(balances, 0, 1, 30)    // returns true, balances is now {70, 80}
//   transfer(balances, 1, 0, 500)   // returns false, balances is still {70, 80}
//   transfer(balances, 0, 7, 10)    // returns false: there is no account 7
//
// Check both accounts before moving any money, so a failure changes nothing.
bool transfer(std::vector<int> &balances, std::size_t from, std::size_t to, int amount) {
    if (from >= balances.size() || to >= balances.size()) return false;
    if (amount > balances[from]) return false;
    if (amount <= 0) return false;

    balances[from] -= amount;
    balances[to] += amount;
    return true;
}

// Return what balances would look like after taking fee from every account.
// A balance smaller than fee drops to 0, never below. fee is never negative.
//
// Example:
//   balances = {100, 3, 0}
//   std::vector<int> preview = after_fee(balances, 5);
//   // preview is {95, 0, 0}, and balances is still {100, 3, 0}
//
// balances is a copy, so the caller's accounts are safe while you change it.
std::vector<int> after_fee(std::vector<int> balances, int fee) {
    std::vector<int> cBal = balances;
    for (int &s : cBal) {
        if (s < fee) {
            s = 0;
            continue;
        };
        s -= fee;
    }

    return cBal;
}
