// Exercise: Matrix
// A rows × cols matrix of doubles with element access, multiplication,
// equality, and printing.
//
// operator() can take any number of arguments, which makes it the usual way to
// index a 2D container: m(row, col). Store the elements in one
// std::vector<double> of rows * cols values, row after row.
//
// Grade: grade 13_operator_overloading/03_matrix

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
