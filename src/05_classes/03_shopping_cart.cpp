// === Lesson: Composition and returning references ============================
//
// Composition means building a class out of other objects: its members can be
// strings, vectors and structs, and its member functions keep them consistent
// with each other. The members are destroyed along with the object, so there's
// no cleanup code to write.
//
// Returning *this by reference lets calls chain. Inside a member function,
// `this` points to the object the function was called on, so *this is that
// object:
//
//     class Query {
//     public:
//         Query &where(const std::string &condition) {
//             conditions_.push_back(condition);
//             return *this;
//         }
//         Query &limit(int rows) {
//             limit_ = rows;
//             return *this;
//         }
//
//         // Read-only access to a member, without copying it.
//         const std::vector<std::string> &conditions() const { return conditions_; }
//
//     private:
//         std::vector<std::string> conditions_;
//         int limit_ = 0;
//     };
//
//     Query q;
//     q.where("age > 30").where("city = 'Oslo'").limit(10);
//     for (const std::string &c : q.conditions()) { ... }   // reads, no copy
//     q.conditions().clear();                              // compile error: const
//
// If where() returned a Query instead of a Query&, each call would return a
// copy, and every call after the first in a chain would change that copy.
// A returned reference is only valid while the object it refers into exists,
// so use it right away rather than storing it somewhere.
//
// To change elements in place, loop with a reference:
//
//     for (std::string &c : conditions_) c += ";";   // changes the elements
//     for (std::string c : conditions_) c += ";";    // changes copies: no effect
//
// To remove the element at index i from a vector (iterators get a proper
// introduction in module 06):
//
//     conditions_.erase(conditions_.begin() + i);   // later elements shift down
//
// When a function can fail, check everything before changing anything. Then a
// throw leaves the object exactly as it was.
//
// Read more: https://www.learncpp.com/cpp-tutorial/composition/
//            https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
//
// === Exercise: Shopping cart =================================================
// A Cart is built out of other types: it owns a vector of Items. add() returns *this by
// reference so calls can chain, and items() gives read-only access without a copy.
//
// ./grade 05_classes/03_shopping_cart

#include <stdexcept>
#include <string>
#include <vector>

struct Item {
    std::string name;
    double price = 0.0;  // per unit
    int quantity = 0;
};

class Cart {
public:
    // Add `quantity` units of an item to the cart, then return the cart.
    // If an item with this name is already in the cart, increase its quantity instead of
    // adding a second entry. The item keeps its original price.
    // Throw std::invalid_argument if quantity <= 0 or price < 0, leaving the cart unchanged.
    //
    // Example:
    //   cart.add("tea", 3.5).add("milk", 1.25).add("tea", 9.99, 2);
    //   // items() is {{"tea", 3.5, 3}, {"milk", 1.25, 1}}
    //   cart.add("tea", 3.5, 0);   // throws; the cart is unchanged
    //
    // Returns *this by reference, so chained calls all change the same cart.
    Cart &add(const std::string &name, double price, int quantity = 1) {
        throw "TODO";
    }

    // Remove the item with this name from the cart completely, whatever its quantity.
    // Return true if it was removed, false if it isn't in the cart.
    // The remaining items keep their order.
    //
    // Example:
    //   cart.add("tea", 3.5, 2).add("milk", 1.25).add("eggs", 3.0);
    //   cart.remove("milk");   // true; the items are now tea, eggs
    //   cart.remove("milk");   // false: milk is already gone
    bool remove(const std::string &name) {
        throw "TODO";
    }

    // Return the total number of units: the sum of every item's quantity.
    //
    // Example:
    //   cart.add("tea", 3.5, 2).add("milk", 1.25);
    //   cart.item_count() is 3   // 2 teas and 1 milk
    int item_count() const {
        throw "TODO";
    }

    // Return the sum of price × quantity over all items.
    // An empty cart totals 0.0.
    //
    // Example:
    //   cart.add("tea", 3.5, 2).add("milk", 1.25);
    //   cart.total() is 8.25   // 3.5 × 2 + 1.25 × 1
    double total() const {
        throw "TODO";
    }

    // Return the items, in the order they were first added.
    //
    // Example:
    //   cart.add("tea", 3.5).add("milk", 1.25).add("tea", 3.5);
    //   cart.items() is {{"tea", 3.5, 2}, {"milk", 1.25, 1}}
    //
    // Returns a const reference, so callers can read the items without copying them.
    const std::vector<Item> &items() const {
        throw "TODO";
    }

private:
    std::vector<Item> items_;
};
