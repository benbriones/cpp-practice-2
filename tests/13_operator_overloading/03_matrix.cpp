#include "grader.hpp"
#include "13_operator_overloading/03_matrix.cpp"

// Builds a Matrix from rows, using your constructor and operator().
Matrix make(const std::vector<std::vector<double>>& values) {
    Matrix m(static_cast<int>(values.size()), static_cast<int>(values[0].size()));
    for (int r = 0; r < m.rows(); ++r) {
        for (int c = 0; c < m.cols(); ++c) m(r, c) = values[r][c];
    }
    return m;
}

// Reads every element back through the const operator().
std::vector<std::vector<double>> rows_of(const Matrix& m) {
    std::vector<std::vector<double>> values(m.rows(), std::vector<double>(m.cols()));
    for (int r = 0; r < m.rows(); ++r) {
        for (int c = 0; c < m.cols(); ++c) values[r][c] = m(r, c);
    }
    return values;
}

TEST("constructor: shape and zeros") {
    const Matrix m(2, 3);
    CHECK_EQ(m.rows(), 2);
    CHECK_EQ(m.cols(), 3);
    CHECK_EQ(rows_of(m), {{0, 0, 0}, {0, 0, 0}});
}

TEST("constructor: sizes must be positive") {
    CHECK_THROWS(std::invalid_argument, Matrix(0, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(2, -1));
}

TEST("operator(): write, then read through a const reference") {
    Matrix m(2, 2);
    m(0, 1) = 5;
    m(1, 0) = -2.5;
    const Matrix& view = m;
    CHECK_EQ(view(0, 1), 5.0);
    CHECK_EQ(view(1, 0), -2.5);
    CHECK_EQ(view(0, 0), 0.0);
}

TEST("operator(): rows and columns aren't mixed up") {
    Matrix m(2, 3);
    m(1, 2) = 7;
    CHECK_EQ(rows_of(m), {{0, 0, 0}, {0, 0, 7}});
}

TEST("operator(): out-of-range positions throw") {
    Matrix m(2, 3);
    const Matrix& view = m;
    CHECK_THROWS(std::out_of_range, m(2, 0));
    CHECK_THROWS(std::out_of_range, m(0, 3));
    CHECK_THROWS(std::out_of_range, m(-1, 0));
    CHECK_THROWS(std::out_of_range, view(0, -1));
}

TEST("identity") {
    CHECK_EQ(rows_of(Matrix::identity(3)), {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    CHECK_EQ(rows_of(Matrix::identity(1)), {{1}});
}

TEST("operator*: 2x2 times 2x2") {
    const Matrix a = make({{1, 2}, {3, 4}});
    const Matrix b = make({{5, 6}, {7, 8}});
    CHECK_EQ(rows_of(a * b), {{19, 22}, {43, 50}});
    CHECK_EQ(rows_of(b * a), {{23, 34}, {31, 46}});
}

TEST("operator*: different shapes") {
    const Matrix a = make({{1, 2, 3}, {4, 5, 6}});
    const Matrix column = make({{1}, {0}, {-1}});
    const Matrix product = a * column;
    CHECK_EQ(product.rows(), 2);
    CHECK_EQ(product.cols(), 1);
    CHECK_EQ(rows_of(product), {{-2}, {-2}});
}

TEST("operator*: mismatched sizes throw") {
    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) * Matrix(2, 3));
}

TEST("operator==") {
    CHECK(make({{1, 2}, {3, 4}}) == make({{1, 2}, {3, 4}}), "equal matrices should be ==");
    CHECK(!(make({{1, 2}, {3, 4}}) == make({{1, 2}, {3, 5}})), "one different element: not ==");
    CHECK(!(Matrix(2, 3) == Matrix(3, 2)), "different shapes: not ==");
    CHECK(!(Matrix(1, 4) == Matrix(2, 2)), "same number of elements, different shape: not ==");
}

TEST("multiplying by the identity changes nothing") {
    const Matrix a = make({{2, -1, 0.5}, {3, 4, 1}});
    CHECK(a * Matrix::identity(3) == a, "a * I should equal a");
    CHECK(Matrix::identity(2) * a == a, "I * a should equal a");
}

TEST("operator<<") {
    std::ostringstream out;
    out << make({{1, 2}, {3, 4.5}}) << make({{-1, 0, 7}});
    CHECK_EQ(out.str(), "1 2\n3 4.5\n-1 0 7\n");
}
