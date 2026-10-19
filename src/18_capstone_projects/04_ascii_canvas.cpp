// Challenge: ASCII canvas
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
// std::vector<std::unique_ptr<Shape>>. Strict integer parsing: std::from_chars
// in <charconv> reports where the number stopped.
//
// ./grade 18_capstone_projects/04_ascii_canvas
// Try it: grade --run 18_capstone_projects/04_ascii_canvas

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
