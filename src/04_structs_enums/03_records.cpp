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
//     for (const Book &b : shelf) { ... }       // read, without copying
//     for (Book &b : shelf) b.title += "!";     // changes the books in shelf
//
// Copying a Book copies its whole title string, so read-only loops should use
// const&. In a reference loop, &b is the address of the element in the vector.
// In a copying loop, &b is the address of a copy that's gone after this
// iteration.
//
// A pointer to a struct reaches its members with ->, short for (*p).member:
//
//     const Book *p = &shelf[1];
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

double total_payroll(const std::vector<Employee> &staff) {
    double total = 0;
    for (const Employee &e : staff) {
        total += e.salary;
    }

    return total;
}

// Return the names of everyone in `department`, in their original order.
// An unknown department gives an empty vector.
//
// Example:
//   staff = {{"Ada", "Engineering", 120000},
//            {"Linus", "Operations", 90000},
//            {"Grace", "Engineering", 135000}}
//   names_in(staff, "Engineering") is {"Ada", "Grace"}
//   names_in(staff, "Marketing") is {}
std::vector<std::string> names_in(const std::vector<Employee> &staff,
                                  const std::string &department) {
    std::vector<std::string> name_results = {};

    for (const Employee &s : staff) {
        if (s.department == department) {
            name_results.push_back(s.name);
        }
    }

    return name_results;
}

// Return a pointer to the best-paid employee in staff.
// If several share the top salary, return the first one.
// If staff is empty, return nullptr.
//
// Example:
//   staff = {{"Ada", "Engineering", 120000},
//            {"Grace", "Engineering", 135000},
//            {"Barbara", "Research", 135000}}
//   const Employee *best = highest_paid(staff);
//   // best == &staff[1], so best->name is "Grace"
//
// Reach members through a pointer with ->:  best->name
const Employee *highest_paid(const std::vector<Employee> &staff) {
    if (staff.empty()) return nullptr;

    const Employee *curr_highest_paid = &staff[0];

    for (const Employee &e : staff) {
        if (e.salary > curr_highest_paid->salary) {
            curr_highest_paid = &e;
        }
    }

    return curr_highest_paid;
}

// Raise every salary in `department` by `percent` percent: 10 means × 1.10.
// Employees in other departments keep their salary.
// An unknown department changes nothing.
//
// Example:
//   staff = {{"Ada", "Engineering", 120000},
//            {"Linus", "Operations", 90000}}
//   give_raise(staff, "Engineering", 10);
//   // Ada's salary is now 132000, Linus's is still 90000
//
// Changes the employees in the caller's vector; returns nothing.
void give_raise(std::vector<Employee> &staff, const std::string &department, double percent) {
    double converted_percent = 1.0 + (percent / 100.0);

    for (Employee &s : staff) {
        if (s.department == department) {
            s.salary *= converted_percent;
        }
    }
}

// Return the lowest and highest salary in staff, as {low, high}.
// staff is never empty. With one employee, low and high are the same.
//
// Example:
//   staff = {{"Ada", "Engineering", 120000},
//            {"Linus", "Operations", 90000},
//            {"Ken", "Operations", 85000}}
//   auto [low, high] = salary_range(staff);
//   // low is 85000, high is 120000
//
// Callers can unpack the pair with a structured binding, as above.
std::pair<double, double> salary_range(const std::vector<Employee> &staff) {
    double curr_max_salary = staff[0].salary;
    double curr_min_salary = staff[0].salary;

    for (const Employee &e : staff) {
        if (e.salary > curr_max_salary) {
            curr_max_salary = e.salary;
        }
        if (e.salary < curr_min_salary) {
            curr_min_salary = e.salary;
        }
    }

    return {curr_min_salary, curr_max_salary};
}
