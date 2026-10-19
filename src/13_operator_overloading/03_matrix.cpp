// === Lesson: operator() and 2D containers ====================================
//
// operator[] takes exactly one argument in C++20, so it can't do grid[r, c].
// operator() (the call operator) takes as many as you like, which makes it the
// usual way to index something two-dimensional: grid(r, c).
//
// A 2D container rarely needs a vector of vectors. One flat std::vector holding
// row 0, then row 1, and so on ("row-major" order) is a single allocation, and
// element (x, y) of a width-wide grid sits at index y * width + x:
//
//     class Image {
//     public:
//         Image(int width, int height)
//             : width_(width), height_(height), pixels_(width * height, 0) {}
//
//         // A named constructor: a static function that builds a ready-made object.
//         static Image square(int side) { return Image(side, side); }
//
//         int& operator()(int x, int y) { return pixels_[y * width_ + x]; }
//         int operator()(int x, int y) const { return pixels_[y * width_ + x]; }
//
//     private:
//         int width_;
//         int height_;
//         std::vector<int> pixels_;
//     };
//
//     Image img(4, 3);
//     img(1, 2) = 255;                   // non-const operator(): returns int&
//     Image icon = Image::square(16);    // static: called on the class itself
//
// As with [], write operator() twice: one returning a reference for writing,
// and a const one for reading through a const Image&.
//
// Parentheses and braces mean different things for vectors:
//
//     std::vector<int> a(3, 0);   // three elements: {0, 0, 0}
//     std::vector<int> b{3, 0};   // two elements: {3, 0}
//
// A vector's [] does no bounds checking. .at() does, but on a flat vector it
// only checks the total size: in a 4-wide image, (4, 0) is index 4, which is
// really pixel (0, 1). Check each coordinate against its own limit instead.
//
// Two std::vectors compare with == element by element.
//
// Read more: https://www.learncpp.com/cpp-tutorial/overloading-the-parenthesis-operator
//            https://www.learncpp.com/cpp-tutorial/static-member-functions/
//
// === Exercise: Matrix ========================================================
// A rows × cols matrix of doubles with element access, multiplication,
// equality, and printing. Store the elements in one std::vector<double> of
// rows * cols values, row after row.
//
// ./grade 13_operator_overloading/03_matrix

#include <ostream>
#include <stdexcept>
#include <vector>

class Matrix {
public:
    // A rows × cols matrix of zeros. Throws std::invalid_argument unless both are positive.
    Matrix(int rows, int cols) {
        throw "TODO";
    }

    // The n × n identity matrix: 1 on the diagonal, 0 everywhere else.
    static Matrix identity(int n) {
        throw "TODO";
    }

    int rows() const {
        throw "TODO";
    }

    int cols() const {
        throw "TODO";
    }

    // m(row, col), counting from 0. Throws std::out_of_range for a position
    // outside the matrix. The non-const version lets you write: m(0, 1) = 5;
    double& operator()(int row, int col) {
        throw "TODO";
    }

    double operator()(int row, int col) const {
        throw "TODO";
    }

private:
    // TODO: data members
};

// The matrix product. Throws std::invalid_argument unless a.cols() == b.rows().
// result(r, c) is the sum over k of a(r, k) * b(k, c).
Matrix operator*(const Matrix& a, const Matrix& b) {
    throw "TODO";
}

// Equal when both the shape and every element match.
bool operator==(const Matrix& a, const Matrix& b) {
    throw "TODO";
}

// One line per row, elements separated by single spaces, each line ending
// with '\n': {{1, 2}, {3, 4}} prints "1 2\n3 4\n". Print numbers with plain <<.
std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    throw "TODO";
}
