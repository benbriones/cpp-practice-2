#include "grader.hpp"
#include "05_classes/03_shopping_cart.cpp"

static std::vector<std::string> names(const Cart &cart) {
    std::vector<std::string> out;
    for (const Item &item : cart.items()) out.push_back(item.name);
    return out;
}

TEST("add: puts a new item in the cart") {
    Cart cart;
    cart.add("tea", 3.5);
    CHECK_EQ(cart.items().size(), 1);
    CHECK_EQ(cart.items()[0].name, "tea");
    CHECK_NEAR(cart.items()[0].price, 3.5);
    CHECK_EQ(cart.items()[0].quantity, 1);
}

TEST("add: uses the quantity argument") {
    Cart cart;
    cart.add("milk", 1.25, 2);
    CHECK_EQ(cart.items().size(), 1);
    CHECK_EQ(cart.items()[0].quantity, 2);
}

TEST("add: calls chain and keep their order") {
    Cart cart;
    cart.add("apples", 0.5, 6).add("bread", 2.25).add("cheese", 4.0);
    CHECK_EQ(names(cart), {"apples", "bread", "cheese"});
}

TEST("add: the same name merges into one entry") {
    Cart cart;
    cart.add("tea", 3.5).add("milk", 1.25).add("tea", 3.5, 2);
    CHECK_EQ(names(cart), {"tea", "milk"});
    CHECK_EQ(cart.items()[0].quantity, 3);
}

TEST("add: a merge keeps the original price") {
    Cart cart;
    cart.add("tea", 3.5).add("tea", 9.99);
    CHECK_EQ(cart.items().size(), 1);
    CHECK_NEAR(cart.items()[0].price, 3.5);
    CHECK_EQ(cart.items()[0].quantity, 2);
}

TEST("add: rejects bad quantities and prices") {
    Cart cart;
    CHECK_THROWS(std::invalid_argument, cart.add("tea", 3.5, 0));
    CHECK_THROWS(std::invalid_argument, cart.add("tea", 3.5, -2));
    CHECK_THROWS(std::invalid_argument, cart.add("tea", -1.0));
    CHECK_EQ(cart.items().size(), 0);
}

TEST("add: a free item is fine") {
    Cart cart;
    cart.add("sample", 0.0);
    CHECK_EQ(cart.item_count(), 1);
}

TEST("item_count: adds up quantities") {
    Cart cart;
    CHECK_EQ(cart.item_count(), 0);
    cart.add("tea", 3.5, 2).add("milk", 1.25);
    CHECK_EQ(cart.item_count(), 3);
}

TEST("total: price times quantity") {
    Cart cart;
    CHECK_NEAR(cart.total(), 0.0);
    cart.add("tea", 3.5, 2).add("milk", 1.25);
    CHECK_NEAR(cart.total(), 8.25);
}

TEST("remove: takes the whole item out") {
    Cart cart;
    cart.add("tea", 3.5, 2).add("milk", 1.25).add("eggs", 3.0);
    CHECK_EQ(cart.remove("milk"), true);
    CHECK_EQ(names(cart), {"tea", "eggs"});
    CHECK_EQ(cart.item_count(), 3);
    CHECK_NEAR(cart.total(), 10.0);
}

TEST("remove: missing items return false") {
    Cart cart;
    CHECK_EQ(cart.remove("tea"), false);
    cart.add("tea", 3.5);
    CHECK_EQ(cart.remove("tea"), true);
    CHECK_EQ(cart.remove("tea"), false);
    CHECK_EQ(cart.items().size(), 0);
}

TEST("Cart: readable through a const reference") {
    Cart cart;
    cart.add("tea", 3.5, 2);
    const Cart &view = cart;
    CHECK_EQ(view.item_count(), 2);
    CHECK_NEAR(view.total(), 7.0);
    CHECK_EQ(view.items().size(), 1);
}
