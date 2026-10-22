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
    // Build a rows × cols matrix with every element set to 0.
    // Throw std::invalid_argument unless both rows and cols are positive.
    //
    // Example:
    //   Matrix m(2, 3);   // m is {{0, 0, 0}, {0, 0, 0}}
    //   Matrix(0, 3) and Matrix(2, -1) throw std::invalid_argument
    Matrix(int rows, int cols) {
        throw "TODO";
    }

    // Return the n × n identity matrix: 1 on the diagonal, 0 everywhere else.
    //
    // Example:
    //   Matrix::identity(3) is {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
    //   Matrix::identity(1) is {{1}}
    //
    // Multiplying a matrix by an identity of the right size leaves it unchanged.
    static Matrix identity(int n) {
        throw "TODO";
    }

    int rows() const {
        throw "TODO";
    }

    int cols() const {
        throw "TODO";
    }

    // Return a reference to the element at m(row, col), counting from 0.
    // Throw std::out_of_range for a position outside the matrix:
    // row must be in [0, rows()) and col must be in [0, cols()).
    //
    // Example:
    //   Matrix m(2, 3);
    //   m(1, 2) = 7;   // m is now {{0, 0, 0}, {0, 0, 7}}
    //   m(2, 0), m(0, 3) and m(-1, 0) throw std::out_of_range
    //
    // The non-const version lets you write: m(0, 1) = 5;
    double& operator()(int row, int col) {
        throw "TODO";
    }

    double operator()(int row, int col) const {
        throw "TODO";
    }

private:
    // TODO: data members
};

// Return the matrix product a * b, which has a.rows() rows and b.cols() columns.
// Throw std::invalid_argument unless a.cols() == b.rows().
// result(r, c) is the sum over k of a(r, k) * b(k, c).
//
// Example:
//   a = {{1, 2}, {3, 4}}, b = {{5, 6}, {7, 8}}
//   a * b is {{19, 22}, {43, 50}}    // result(0, 0) = 1*5 + 2*7 = 19
//   b * a is {{23, 34}, {31, 46}}    // order matters
//   Matrix(2, 3) * Matrix(2, 3) throws std::invalid_argument
Matrix operator*(const Matrix& a, const Matrix& b) {
    throw "TODO";
}

// Return true when both the shape and every element match.
//
// Example:
//   {{1, 2}, {3, 4}} == {{1, 2}, {3, 4}} is true
//   {{1, 2}, {3, 4}} == {{1, 2}, {3, 5}} is false
//   Matrix(1, 4) == Matrix(2, 2) is false: same element count, different shape
bool operator==(const Matrix& a, const Matrix& b) {
    throw "TODO";
}

// Print m with one line per row, each line ending with '\n'.
// Separate the elements in a row with single spaces.
// Print numbers with plain <<.
//
// Example:
//   {{1, 2}, {3, 4}} prints "1 2\n3 4\n"
//   {{1, 2}, {3, 4.5}} prints "1 2\n3 4.5\n"
std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    throw "TODO";
}
