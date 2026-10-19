// Exercise: Records
// A vector of structs is C++'s list of records. Loop over it by reference to
// avoid copying every element:
//
//   for (const Employee& e : staff) { ... }   // read
//   for (Employee& e : staff) { ... }         // modify
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
