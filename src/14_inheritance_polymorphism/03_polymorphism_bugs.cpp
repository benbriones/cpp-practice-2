// Exercise: Polymorphism bugs
// This code compiles but has three bugs, so some tests fail from the start.
// Run grade to see them, then fix them. You may change types and signatures;
// the tests only rely on the names. Then implement count_dogs at the bottom.
//
// The usual suspects: storing derived objects by value in a container of the
// base class (slicing), deleting through a base pointer without a virtual
// destructor, and a derived function that hides a base function instead of
// overriding it.
//
// ./grade 14_inheritance_polymorphism/03_polymorphism_bugs

#include <memory>
#include <string>
#include <vector>

// How many Dog objects exist right now; the tests use it to spot skipped destructors.
inline int live_dogs = 0;

class Animal {
public:
    explicit Animal(std::string name) : name_(std::move(name)) {}
    ~Animal() {}

    const std::string& name() const { return name_; }
    virtual std::string sound() const { return "..."; }
    std::string how_it_moves() const { return "walks"; }

    // "Rex says Woof"
    std::string describe() const { return name_ + " says " + sound(); }

private:
    std::string name_;
};

class Dog : public Animal {
public:
    explicit Dog(std::string name) : Animal(std::move(name)) { ++live_dogs; }
    ~Dog() { --live_dogs; }

    std::string sound() const override { return "Woof"; }
};

class Cat : public Animal {
public:
    explicit Cat(std::string name) : Animal(std::move(name)) {}

    std::string sound() const override { return "Meow"; }
};

class Bird : public Animal {
public:
    explicit Bird(std::string name) : Animal(std::move(name)) {}

    std::string sound() const override { return "Tweet"; }
    std::string how_it_moves() const { return "flies"; }
};

// The zoo the tests use: a Dog named Rex and a Cat named Tom, in that order.
std::vector<Animal> make_zoo() {
    std::vector<Animal> zoo;
    zoo.push_back(Dog("Rex"));
    zoo.push_back(Cat("Tom"));
    return zoo;
}

// Every animal's describe() line, in zoo order.
std::vector<std::string> chorus(const std::vector<Animal>& zoo) {
    std::vector<std::string> lines;
    for (const Animal& animal : zoo) lines.push_back(animal.describe());
    return lines;
}

// A new pet the caller owns through an Animal pointer.
std::unique_ptr<Animal> adopt_dog(const std::string& name) {
    return std::make_unique<Dog>(name);
}

// "Tweety flies", "Rex walks"
std::string travel(const Animal& animal) {
    return animal.name() + " " + animal.how_it_moves();
}

// How many of the animals are Dogs. dynamic_cast<const Dog*>(p) gives nullptr
// when p doesn't point at a Dog (or something derived from Dog).
int count_dogs(const std::vector<const Animal*>& animals) {
    throw "TODO";
}
