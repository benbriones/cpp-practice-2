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
//         Query& where(const std::string& condition) {
//             conditions_.push_back(condition);
//             return *this;
//         }
//         Query& limit(int rows) {
//             limit_ = rows;
//             return *this;
//         }
//
//         // Read-only access to a member, without copying it.
//         const std::vector<std::string>& conditions() const { return conditions_; }
//
//     private:
//         std::vector<std::string> conditions_;
//         int limit_ = 0;
//     };
//
//     Query q;
//     q.where("age > 30").where("city = 'Oslo'").limit(10);
//     for (const std::string& c : q.conditions()) { ... }   // reads, no copy
//     q.conditions().clear();                              // compile error: const
//
// If where() returned a Query instead of a Query&, each call would return a
// copy, and every call after the first in a chain would change that copy.
// A returned reference is only valid while the object it refers into exists,
// so use it right away rather than storing it somewhere.
//
// To change elements in place, loop with a reference:
//
//     for (std::string& c : conditions_) c += ";";   // changes the elements
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
    // Add `quantity` units of an item. If an item with this name is already in the cart,
    // increase its quantity (keeping its original price) instead of adding a second entry.
    // Throw std::invalid_argument if quantity <= 0 or price < 0, leaving the cart unchanged.
    Cart& add(const std::string& name, double price, int quantity = 1) {
        throw "TODO";
    }

    // Remove the item with this name completely. Return false if it isn't in the cart.
    bool remove(const std::string& name) {
        throw "TODO";
    }

    // Total number of units: 2 teas and 1 milk is 3.
    int item_count() const {
        throw "TODO";
    }

    // Sum of price × quantity over all items.
    double total() const {
        throw "TODO";
    }

    // The items, in the order they were first added.
    const std::vector<Item>& items() const {
        throw "TODO";
    }

private:
    std::vector<Item> items_;
};
