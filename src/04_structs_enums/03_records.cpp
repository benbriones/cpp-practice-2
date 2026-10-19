// === Lesson: Vectors of structs ==============================================
//
// A std::vector of structs is C++'s list of records, the counterpart of an array
// of objects in JavaScript:
//
//     struct Book {
//         std::string title;
//         int year{};
//     };
//     std::vector<Book> shelf{{"Dune", 1965}, {"Emma", 1815}};
//     shelf.push_back({"Ulysses", 1922});
//
// The loop variable decides whether you get copies or the elements themselves:
//
//     for (Book b : shelf) b.year = 0;          // copies: shelf is unchanged
//     for (const Book& b : shelf) { ... }       // read, without copying
//     for (Book& b : shelf) b.title += "!";     // changes the books in shelf
//
// Copying a Book copies its whole title string, so read-only loops should use
// const&. In a reference loop, &b is the address of the element in the vector.
// In a copying loop, &b is the address of a copy that's gone after this
// iteration.
//
// A pointer to a struct reaches its members with ->, short for (*p).member:
//
//     const Book* p = &shelf[1];
//     std::cout << p->title;                    // same as (*p).title
//
// A `const Book*` lets you read the book but not change it, which is what a
// function holding a const vector can hand out. nullptr says "no book".
//
// When a function produces two values, std::pair (from <utility>) bundles them.
// Its parts are .first and .second, and a braced list builds one. A structured
// binding unpacks a pair, or any struct, into named variables:
//
//     std::pair<int, int> span{1815, 1965};
//     auto [oldest, newest] = span;             // oldest == 1815, newest == 1965
//     auto [title, year] = shelf[0];            // structs too (this copies)
//
// Running totals: start from a value of the right type. `auto sum = 0;` is an
// int, so adding doubles to it throws away their fractions.
//
// Read more: https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/
//            https://en.cppreference.com/w/cpp/language/structured_binding
//
// === Exercise: Records =======================================================
// Implement the five functions below.
//
// ./grade 04_structs_enums/03_records

#include <string>
#include <utility>
#include <vector>

struct Employee {
    std::string name;
    std::string department;
    double salary{};
};

double total_payroll(const std::vector<Employee>& staff) {
    throw "TODO";
}

// Names of everyone in `department`, in their original order.
std::vector<std::string> names_in(const std::vector<Employee>& staff,
                                  const std::string& department) {
    throw "TODO";
}

// A pointer to the best-paid employee (the first one, on ties), or nullptr if
// staff is empty. Reach members through a pointer with ->:  best->name
const Employee* highest_paid(const std::vector<Employee>& staff) {
    throw "TODO";
}

// Raise every salary in `department` by `percent` percent: 10 means × 1.10.
void give_raise(std::vector<Employee>& staff, const std::string& department, double percent) {
    throw "TODO";
}

// The lowest and highest salary, as {low, high}. staff is never empty.
// Callers can unpack the pair:  auto [low, high] = salary_range(staff);
std::pair<double, double> salary_range(const std::vector<Employee>& staff) {
    throw "TODO";
}
