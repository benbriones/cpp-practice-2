// === Lesson: Abstract classes and owning base pointers =======================
//
// `= 0` declares a pure virtual function: a promise with no body. A class with
// one is abstract. You can't create one on its own, only classes derived from it
// that override every pure virtual function:
//
//     class Instrument {
//     public:
//         virtual ~Instrument() = default;
//         virtual std::string play() const = 0;
//     };
//
//     class Drum : public Instrument {
//     public:
//         std::string play() const override { return "boom"; }
//     };
//
//     Instrument i;   // error: Instrument is an abstract class
//     Drum d;         // fine
//
// Forget to override one of them and the derived class is abstract too; the
// error shows up where you try to create one.
//
// Polymorphism needs the original object, reached through a pointer or a
// reference: a std::vector<Instrument> can't hold a Drum. A vector of
// std::unique_ptr<Instrument> can, and it deletes each object for you:
//
//     std::vector<std::unique_ptr<Instrument>> band;
//     band.push_back(std::make_unique<Drum>());   // unique_ptr<Drum> converts
//     for (const auto &player : band) {
//         std::cout << player->play() << '\n';      // each object's own play()
//     }
//
//     const Instrument *first = band[0].get();   // a plain pointer: look, don't own
//
// A function returning std::unique_ptr<Base> can create any derived class and
// hand it to the caller, or return nullptr for "nothing".
//
// A constructor that throws never finishes, so no object exists and nothing
// leaks. To turn that into a nullptr, catch the exception around the creation.
//
// Parsing words and numbers from text is a job for std::istringstream (module
// 09). `in >> x` is false when it fails. To detect extra input after the last
// value you expect, try to read one more: if that succeeds, there was too much.
//
// Read more: https://en.cppreference.com/w/cpp/language/abstract_class
//            https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
//
// === Exercise: Shapes ========================================================
// Implement three shapes that derive from the abstract class Shape, then use
// them through Shape pointers. std::numbers::pi is in <numbers>.
//
// ./grade 14_inheritance_polymorphism/02_shapes

#include <cmath>
#include <memory>
#include <numbers>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
};

// Every constructor throws std::invalid_argument for a size that isn't positive.

class Circle : public Shape {
public:
    explicit Circle(double radius) {
        throw "TODO";
    }

    double area() const override {
        throw "TODO";
    }

    double perimeter() const override {
        throw "TODO";
    }

    // Return this shape's name: "circle".
    std::string name() const override {
        throw "TODO";
    }

private:
    // TODO: data members
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) {
        throw "TODO";
    }

    double area() const override {
        throw "TODO";
    }

    double perimeter() const override {
        throw "TODO";
    }

    // Return this shape's name: "rectangle".
    std::string name() const override {
        throw "TODO";
    }

private:
    // TODO: data members
};

// A triangle with sides a, b and c.
// Like the other shapes, a side that isn't positive throws std::invalid_argument.
// Also throws if the sides can't form a triangle: each side must be shorter
// than the other two added together.
// Area by Heron's formula: with s half the perimeter, area = sqrt(s(s-a)(s-b)(s-c)).
//
// Example:
//   Triangle(3, 4, 5): perimeter 12, s = 6, area = sqrt(6 * 3 * 2 * 1) = 6
//   Triangle(1, 2, 3) throws: 3 isn't shorter than 1 + 2
//   Triangle(3, 0, 3) throws: 0 isn't positive
class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) {
        throw "TODO";
    }

    double area() const override {
        throw "TODO";
    }

    double perimeter() const override {
        throw "TODO";
    }

    // Return this shape's name: "triangle".
    std::string name() const override {
        throw "TODO";
    }

private:
    // TODO: data members
};

double total_area(const std::vector<std::unique_ptr<Shape>> &shapes) {
    throw "TODO";
}

// Return the shape with the largest area, or nullptr if there are none.
// On a tie, return the first one.
//
// Example:
//   shapes = {Circle(1), Rectangle(2, 3), Triangle(3, 4, 5)}   // areas pi, 6, 6
//   largest(shapes) is shapes[1].get(): the rectangle comes before the tied triangle
//   largest({}) is nullptr
//
// The plain pointer only looks at the shape; the vector still owns it.
const Shape *largest(const std::vector<std::unique_ptr<Shape>> &shapes) {
    throw "TODO";
}

// Build a shape from text: "circle 2", "rectangle 3 4", "triangle 3 4 5".
// Extra spaces are fine, and sizes may have decimals.
// Return nullptr for an unknown name, missing or extra numbers,
// or sizes the constructor rejects (catch its exception).
//
// Example:
//   make_shape("rectangle 3 4") is a rectangle with area 12
//   make_shape("  rectangle   2.5  4 ") is a rectangle with area 10
//   "hexagon 2", "circle", "circle 2 3" and "circle abc" give nullptr
//   "circle -1" and "triangle 1 2 3" give nullptr: the constructor throws
//
// The caller owns the new shape through the returned unique_ptr.
std::unique_ptr<Shape> make_shape(std::string_view spec) {
    throw "TODO";
}
