// === Lesson: Slicing, virtual destructors and hiding =========================
//
// Three classic inheritance bugs. All of them compile without complaint.
//
// Slicing: copying a derived object into a base-class object keeps only the base
// part. The copy really is a base object, so virtual calls on it run the base
// versions:
//
//     struct Base {
//         virtual ~Base() = default;
//         virtual std::string who() const { return "base"; }
//     };
//     struct Derived : Base {
//         std::string who() const override { return "derived"; }
//     };
//
//     Derived d;
//     Base copy = d;   // sliced: copy.who() is "base"
//     Base& ref = d;   // no copy: ref.who() is "derived"
//
// The same happens when a function takes a Base by value, or when derived
// objects are stored in a container of Base values. Polymorphism needs a
// reference or a pointer to the original object.
//
// Deleting through a base pointer: when an object is destroyed through a Base*
// or a std::unique_ptr<Base>, the destructor is called through Base. If ~Base()
// isn't virtual, ~Derived() never runs, and the behaviour is undefined.
//
// Hiding instead of overriding: a derived function with the same name as a
// non-virtual base function hides it. Calls through the derived type find the
// new one, but calls through a Base& are decided at compile time and still run
// the base version:
//
//     struct Shape { std::string kind() const { return "shape"; } };   // not virtual
//     struct Square : Shape { std::string kind() const { return "square"; } };
//
//     Square sq;
//     sq.kind();                              // "square"
//     static_cast<const Shape&>(sq).kind();   // "shape"
//
// Writing `override` on every replacement turns this mistake into a compile
// error, because override is only allowed when the base function is virtual.
//
// dynamic_cast<const Derived*>(p) checks at run time whether p points at a
// Derived (or a class derived from it) and gives nullptr if not. It needs a
// class with at least one virtual function.
//
// Read more: https://www.learncpp.com/cpp-tutorial/object-slicing/
//            https://www.learncpp.com/cpp-tutorial/dynamic-casting/
//
// === Exercise: Polymorphism bugs =============================================
// This code compiles but has three bugs, so some tests fail from the start.
// Run grade to see them, then fix them. You may change types and signatures;
// the tests only rely on the names. Then implement count_dogs at the bottom.
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

    // Return the line "<name> says <sound>".
    //
    // Example:
    //   Dog("Rex").describe() is "Rex says Woof"
    //   Cat("Tom").describe() is "Tom says Meow"
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

// Return the zoo the tests use: a Dog named Rex and a Cat named Tom, in that order.
std::vector<Animal> make_zoo() {
    std::vector<Animal> zoo;
    zoo.push_back(Dog("Rex"));
    zoo.push_back(Cat("Tom"));
    return zoo;
}

// Return every animal's describe() line, in zoo order.
//
// Example:
//   chorus(make_zoo()) is {"Rex says Woof", "Tom says Meow"}
std::vector<std::string> chorus(const std::vector<Animal>& zoo) {
    std::vector<std::string> lines;
    for (const Animal& animal : zoo) lines.push_back(animal.describe());
    return lines;
}

// Return a new Dog called name, as a pet the caller owns through an Animal pointer.
//
// Example:
//   auto pet = adopt_dog("Fido");
//   // pet->describe() is "Fido says Woof"
std::unique_ptr<Animal> adopt_dog(const std::string& name) {
    return std::make_unique<Dog>(name);
}

// Return the animal's name, a space, then how it moves.
//
// Example:
//   travel(Bird("Tweety")) is "Tweety flies"
//   travel(Dog("Rex")) is "Rex walks"
std::string travel(const Animal& animal) {
    return animal.name() + " " + animal.how_it_moves();
}

// Return how many of the animals are Dogs. An empty list returns 0.
// dynamic_cast<const Dog*>(p) gives nullptr
// when p doesn't point at a Dog (or something derived from Dog).
//
// Example:
//   rex and fido are Dogs, tom is a Cat, tweety is a Bird
//   count_dogs({&rex, &tom, &tweety, &fido}) returns 2
//   count_dogs({&tom, &tweety}) returns 0
int count_dogs(const std::vector<const Animal*>& animals) {
    throw "TODO";
}
