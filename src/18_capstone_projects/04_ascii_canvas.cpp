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
    // Create a width × height canvas with every cell set to ' ' (blank).
    // Throw std::invalid_argument unless both width and height are at least 1.
    //
    // Example:
    //   Canvas canvas(3, 2);   // two rows of three spaces
    //   Canvas(0, 5);          // throws std::invalid_argument
    //   Canvas(5, -1);         // throws std::invalid_argument
    Canvas(int width, int height) {
        throw "TODO";
    }

    int width() const {
        throw "TODO";
    }

    int height() const {
        throw "TODO";
    }

    // Set the cell at column x, row y to c.
    // (0, 0) is the top-left cell, and y grows downward.
    // Do nothing if (x, y) is outside the canvas.
    //
    // Example:
    //   Canvas canvas(3, 2);
    //   canvas.set(2, 1, 'b');    // the bottom-right cell is now 'b'
    //   canvas.set(-1, 0, 'x');   // outside the canvas: ignored
    //
    // If every shape draws through set, no shape has to clip itself.
    void set(int x, int y, char c) {
        throw "TODO";
    }

    // Return the character in the cell at column x, row y.
    // Return ' ' if (x, y) is outside the canvas.
    //
    // Example:
    //   Canvas canvas(3, 2);
    //   canvas.set(0, 0, 'a');
    //   canvas.get(0, 0);   // 'a'
    //   canvas.get(1, 0);   // ' ', since nothing was drawn there
    //   canvas.get(5, 5);   // ' ', since it's outside the canvas
    char get(int x, int y) const {
        throw "TODO";
    }

    // Return the grid inside a border, as one string.
    // The top and bottom border lines are '+', one '-' per column, then '+'.
    // Each grid row is wrapped in '|' on both sides.
    // Every line, including the last one, ends in '\n'.
    //
    // Example:
    //   Canvas canvas(3, 1);
    //   canvas.set(1, 0, 'a');
    //   canvas.render() is "+---+\n| a |\n+---+\n", which prints as:
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

// Turn one shape line (never the canvas line) into the matching shape.
// Return nullptr if the line isn't a valid shape: an unknown kind, the wrong number of
// words, a number that isn't a strict integer, a width or height below 1, a <char>
// that isn't one character, or a line that isn't horizontal, vertical or 45° diagonal.
//
// Example:
//   parse_shape("point 1 1 #")      // a shape that draws '#' at (1, 1)
//   parse_shape("rect 0 0 4 3 #")   // a 4 × 3 outline with its top-left corner at (0, 0)
//   parse_shape("point 1.5 2 #")    // nullptr: 1.5 isn't an integer
//   parse_shape("line 0 0 3 1 -")   // nullptr: not horizontal, vertical or 45° diagonal
//
// It returns std::unique_ptr<Shape>, so the caller can own any kind of shape.
std::unique_ptr<Shape> parse_shape(std::string_view line) {
    throw "TODO";
}

int main() {
    throw "TODO";
}
