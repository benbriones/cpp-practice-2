// Exercise: Shopping cart
// A Cart is built out of other types: it owns a vector of Items (composition).
//
// add() returns *this by reference, so calls can chain:
//     cart.add("tea", 3.50).add("milk", 1.25, 2);
// items() returns a const reference: callers can read the cart's vector without
// copying it, but can't modify it.
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
