// === Lesson: Building objects from text ======================================
//
// A factory function reads some input and decides which derived class to
// create. It returns a std::unique_ptr to the base class, so the caller can own
// any kind of object without knowing which, or nullptr when the input is bad:
//
//     class Animal {
//     public:
//         virtual ~Animal() = default;     // needed to delete through Animal*
//         virtual std::string sound() const = 0;
//     };
//
//     class Dog : public Animal {
//     public:
//         std::string sound() const override { return "woof"; }
//     };
//
//     std::unique_ptr<Animal> make_animal(std::string_view kind) {
//         if (kind == "dog") return std::make_unique<Dog>();   // becomes an Animal ptr
//         return nullptr;                                       // unknown kind
//     }
//
//     std::vector<std::unique_ptr<Animal>> zoo;
//     if (auto animal = make_animal("dog")) zoo.push_back(std::move(animal));
//     for (const auto& a : zoo) std::cout << a->sound() << '\n';
//
// Strict number parsing. std::stoi("3x") returns 3 and std::stoi(" 3") skips
// the space; to reject such input, use std::from_chars from <charconv>. It never
// skips spaces, accepts '-' but not '+', never throws, and reports where it
// stopped:
//
//     std::string_view text = "8080";
//     int port = 0;
//     auto [end, error] =
//         std::from_chars(text.data(), text.data() + text.size(), port);
//     bool ok = error == std::errc{} && end == text.data() + text.size();
//
// error is std::errc{} on success (std::errc::invalid_argument with no digits,
// std::errc::result_out_of_range when the number doesn't fit), and end must
// reach the end of the text, or something followed the digits.
//
// A grid of characters can be a std::vector<std::string>, one string per row,
// or one std::vector<char> where cell (x, y) is at index y * width + x.
//
// Handle edge cases in one place: if every write to the grid goes through one
// function that ignores cells outside it, no shape has to clip itself.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
//            https://en.cppreference.com/w/cpp/utility/from_chars
//
// === Challenge: ASCII canvas =================================================
// Draw shapes onto a grid of characters and print it.
//
// Input: the first non-blank line is "canvas <width> <height>", then one shape
// per line:
//     point <x> <y> <char>
//     rect  <x> <y> <width> <height> <char>     outline only
//     fill  <x> <y> <width> <height> <char>     solid
//     line  <x1> <y1> <x2> <y2> <char>          horizontal, vertical or 45° diagonal only
//     text  <x> <y> <word>                      the word, left to right
// (0, 0) is the top-left cell; y grows downward. Coordinates are integers and
// may be negative; widths and heights are at least 1; <char> is one character.
// Shapes draw in order, later ones on top; anything off the canvas is clipped.
// Skip lines that aren't a valid shape (a note on std::cerr is fine; stderr
// isn't graded). Blank lines are ignored. At the end, print the canvas inside
// a border, as Canvas::render() describes. If the canvas line is missing or
// invalid, print "error: expected 'canvas <width> <height>'" and return 1.
//
// Design: one class per shape kind, each overriding Shape::draw; parse_shape
// turns a line into the right one; main keeps them in a
// std::vector<std::unique_ptr<Shape>>. Parse integers strictly.
//
// ./grade 18_capstone_projects/04_ascii_canvas
// Try it: ./grade --run 18_capstone_projects/04_ascii_canvas

#include <charconv>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class Canvas {
public:
    // A blank canvas (all spaces). Throws std::invalid_argument unless both
    // sizes are at least 1.
    Canvas(int width, int height) {
        throw "TODO";
    }

    int width() const {
        throw "TODO";
    }

    int height() const {
        throw "TODO";
    }

    // Writes one cell; does nothing outside the canvas.
    void set(int x, int y, char c) {
        throw "TODO";
    }

    // Reads one cell; ' ' outside the canvas.
    char get(int x, int y) const {
        throw "TODO";
    }

    // The grid inside a border, each line ending in '\n'. A 3×1 canvas with
    // an 'a' in the middle renders as:
    //     +---+
    //     | a |
    //     +---+
    std::string render() const {
        throw "TODO";
    }

private:
    // TODO: your data members
};

// Given: the interface every shape implements.
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(Canvas& canvas) const = 0;
};

// TODO: your shape classes

// One shape line (not the canvas line) → a shape, or nullptr if the line isn't
// a valid shape.
std::unique_ptr<Shape> parse_shape(std::string_view line) {
    throw "TODO";
}

int main() {
    throw "TODO";
}
