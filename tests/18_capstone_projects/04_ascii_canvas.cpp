#include "grader.hpp"
#include "18_capstone_projects/04_ascii_canvas.cpp"

// The canvas rows as strings, top to bottom, without the border.
std::vector<std::string> rows(const Canvas &canvas) {
    std::vector<std::string> out;
    for (int y = 0; y < canvas.height(); ++y) {
        std::string row;
        for (int x = 0; x < canvas.width(); ++x) row += canvas.get(x, y);
        out.push_back(row);
    }
    return out;
}

// Parses each line and draws it onto a fresh canvas.
std::vector<std::string> draw_all(int width, int height, const std::vector<std::string> &lines) {
    Canvas canvas(width, height);
    for (const auto &line : lines) {
        std::unique_ptr<Shape> shape = parse_shape(line);
        if (!shape) throw grader::Failure{"parse_shape(\"" + line + "\") returned nullptr for a valid shape"};
        shape->draw(canvas);
    }
    return rows(canvas);
}

TEST("Canvas: starts blank") {
    Canvas canvas(3, 2);
    CHECK_EQ(canvas.width(), 3);
    CHECK_EQ(canvas.height(), 2);
    CHECK_EQ(rows(canvas), {"   ", "   "});
}

TEST("Canvas: set and get") {
    Canvas canvas(3, 2);
    canvas.set(0, 0, 'a');
    canvas.set(2, 1, 'b');
    CHECK_EQ(canvas.get(0, 0), 'a');
    CHECK_EQ(canvas.get(2, 1), 'b');
    CHECK_EQ(rows(canvas), {"a  ", "  b"});
}

TEST("Canvas: outside the edges is ignored") {
    Canvas canvas(2, 2);
    canvas.set(-1, 0, 'x');
    canvas.set(2, 0, 'x');
    canvas.set(0, 2, 'x');
    canvas.set(0, -5, 'x');
    CHECK_EQ(rows(canvas), {"  ", "  "});
    CHECK_EQ(canvas.get(5, 5), ' ');
    CHECK_EQ(canvas.get(-1, 0), ' ');
}

TEST("Canvas: rejects sizes below 1") {
    CHECK_THROWS(std::invalid_argument, Canvas(0, 5));
    CHECK_THROWS(std::invalid_argument, Canvas(5, -1));
}

TEST("Canvas: render draws a border") {
    Canvas canvas(3, 2);
    canvas.set(1, 0, 'a');
    CHECK_EQ(canvas.render(), "+---+\n| a |\n|   |\n+---+\n");
}

TEST("point") {
    CHECK_EQ(draw_all(3, 2, {"point 1 1 #"}), {"   ", " # "});
}

TEST("rect: outline only") {
    CHECK_EQ(draw_all(5, 4, {"rect 0 0 4 3 #"}), {"#### ", "#  # ", "#### ", "     "});
}

TEST("rect: one cell wide is a line") {
    CHECK_EQ(draw_all(3, 3, {"rect 1 0 1 3 |"}), {" | ", " | ", " | "});
}

TEST("fill: solid") {
    CHECK_EQ(draw_all(4, 3, {"fill 1 1 2 2 ="}), {"    ", " == ", " == "});
}

TEST("line: horizontal and vertical, either direction") {
    CHECK_EQ(draw_all(4, 3, {"line 3 0 0 0 -"}), {"----", "    ", "    "});
    CHECK_EQ(draw_all(3, 3, {"line 1 2 1 0 |"}), {" | ", " | ", " | "});
}

TEST("line: diagonals") {
    CHECK_EQ(draw_all(3, 3, {"line 0 0 2 2 x", "line 2 0 0 2 o"}), {"x o", " o ", "o x"});
}

TEST("text") {
    CHECK_EQ(draw_all(7, 1, {"text 1 0 hello"}), {" hello "});
}

TEST("later shapes draw on top") {
    CHECK_EQ(draw_all(3, 1, {"fill 0 0 3 1 a", "point 1 0 b"}), {"aba"});
}

TEST("shapes are clipped at the edges") {
    CHECK_EQ(draw_all(3, 2, {"fill -1 -1 3 2 #", "line -5 -5 10 10 \\", "text 1 1 overflow"}),
             {"\\# ", " ov"});
}

TEST("parse_shape: invalid lines give nullptr") {
    for (std::string line : {"circle 1 1 2 @", "point 1 #", "point 1 2 # extra", "point a 2 #",
                             "point 1 2 ##", "rect 0 0 0 3 #", "fill 0 0 2 -1 #", "line 0 0 3 1 -",
                             "text 1 1", "point 1.5 2 #", "", "point 3x 2 #"}) {
        CHECK(parse_shape(line) == nullptr, "parse_shape(\"" + line + "\") should return nullptr");
    }
}

PROGRAM_TEST("A framed scene", {
    .input = "canvas 10 5\n"
             "rect 0 0 10 5 #\n"
             "text 2 2 hello\n"
             "point 9 4 *\n",
    .output = "+----------+\n"
              "|##########|\n"
              "|#        #|\n"
              "|# hello  #|\n"
              "|#        #|\n"
              "|#########*|\n"
              "+----------+\n",
});

PROGRAM_TEST("Crossing lines", {
    .input = "canvas 5 5\n"
             "line 0 0 4 4 x\n"
             "line 4 0 0 4 o\n"
             "line 2 0 2 4 |\n",
    .output = "+-----+\n"
              "|x | o|\n"
              "| x|o |\n"
              "|  |  |\n"
              "| o|x |\n"
              "|o | x|\n"
              "+-----+\n",
});

PROGRAM_TEST("Clipping, and invalid lines are skipped", {
    .input = "canvas 6 3\n"
             "fill -2 -1 4 3 =\n"
             "circle 1 1 1 @\n"
             "rect 3 1 5 5 +\n"
             "\n"
             "point 9 9 !\n",
    .output = "+------+\n"
              "|==    |\n"
              "|== +++|\n"
              "|   +  |\n"
              "+------+\n",
});

PROGRAM_TEST("Just a canvas, after blank lines", {
    .input = "\n\ncanvas 3 1\n",
    .output = "+---+\n|   |\n+---+\n",
});

PROGRAM_TEST("Missing canvas line", {
    .input = "point 1 1 #\n",
    .output = "error: expected 'canvas <width> <height>'\n",
    .exit_code = 1,
});

PROGRAM_TEST("Invalid canvas size", {
    .input = "canvas 0 4\npoint 0 0 #\n",
    .output = "error: expected 'canvas <width> <height>'\n",
    .exit_code = 1,
});
