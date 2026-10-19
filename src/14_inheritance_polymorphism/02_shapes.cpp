// Exercise: Shapes
// Implement three shapes that derive from the abstract class Shape, then use
// them through Shape pointers.
//
// `= 0` makes a function pure virtual: Shape can't be created on its own, and
// every concrete shape must override all three functions. std::numbers::pi is
// in <numbers>.
//
// Grade: grade 14_inheritance_polymorphism/02_shapes

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

    // "circle"
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

    // "rectangle"
    std::string name() const override {
        throw "TODO";
    }

private:
    // TODO: data members
};

// Also throws if the sides can't form a triangle: each side must be shorter
// than the other two added together. Area by Heron's formula: with s half the
// perimeter, area = sqrt(s(s-a)(s-b)(s-c)).
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

    // "triangle"
    std::string name() const override {
        throw "TODO";
    }

private:
    // TODO: data members
};

double total_area(const std::vector<std::unique_ptr<Shape>>& shapes) {
    throw "TODO";
}

// The shape with the largest area (the first one on a tie), or nullptr if there are none.
const Shape* largest(const std::vector<std::unique_ptr<Shape>>& shapes) {
    throw "TODO";
}

// Builds a shape from text: "circle 2", "rectangle 3 4", "triangle 3 4 5".
// Extra spaces are fine. Returns nullptr for an unknown name, missing or extra
// numbers, or sizes the constructor rejects (catch its exception).
std::unique_ptr<Shape> make_shape(std::string_view spec) {
    throw "TODO";
}
