// === Lesson: Parameter bugs ==================================================
//
// A signature that's one character off still compiles, and then the function
// quietly works on the wrong box. These are the usual suspects:
//
// 1. A copy where you meant the caller's data. A by-value parameter, a local
//    initialized from a parameter (std::vector<int> v = values;) and a range-for
//    without & all make copies, and changing a copy changes nothing else.
//
// 2. Out parameters by value. void split(int total, int minutes, int seconds)
//    can never deliver its results: each one is written into the function's own
//    box and thrown away at the closing brace.
//
// 3. Moving a pointer that was passed by value. p = &x inside the function only
//    moves the function's copy. To re-point the caller's pointer, take int *&p
//    or int **pp. The same goes for a loop over a vector of pointers:
//    for (int *p : ptrs) copies each pointer, and for (int *&p : ptrs) names the
//    one inside ptrs.
//
// 4. Aliasing through const&. const int &amount promises that the function won't
//    change amount, not that amount won't change. If the caller passes one of the
//    elements you're modifying, it changes under you partway through. A small
//    value taken by value is copied once, before anything changes.
//
// 5. Handing back a pointer into a copy. If values is a by-value parameter,
//    &values[i] points into the copy's elements, which are freed along with the
//    copy. The caller gets a dangling pointer to something that was never theirs.
//
// 6. Copying when the copy is the point is not a bug. A by-value parameter that
//    the function changes and then returns is exactly right.
//
// The compiler can help with 2 and 3: "parameter set but not used" means a write
// went into a copy nobody reads. grade lists warnings after the results.
//
// Each fix is small: adding or removing an & on a parameter, a local or a loop
// variable. If a fix takes a rewrite, look again.
//
// Read more: https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/
//            https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/
//
// === Challenge: Parameter bugs ===============================================
// Every function below compiles and looks reasonable, but seven of the eight
// have a parameter-passing bug. Run grade, read what fails, and fix all seven.
// Keep each function's name, return type and parameter order; the bugs are in
// the types of parameters and locals.
//
// ./grade 03c_even_more_references_pointers/06_parameter_bugs

#include <cstddef>
#include <string>
#include <vector>

// Append tag to tags, unless tags already holds it.
//
// Example:
//   tags = {"red"}
//   add_tag(tags, "blue");   // tags is now {"red", "blue"}
//   add_tag(tags, "red");    // tags is unchanged
void add_tag(std::vector<std::string> &tags, const std::string &tag) {
    for (const std::string &existing : tags) {
        if (existing == tag) return;
    }
    tags.push_back(tag);
}

// Split total seconds into whole minutes and leftover seconds.
// total is never negative.
//
// Example:
//   int m = 0;
//   int s = 0;
//   split_time(135, m, s);   // m is now 2, s is 15
void split_time(int total, int &minutes, int &seconds) {
    minutes = total / 60;
    seconds = total % 60;
}

// Return text with every space replaced by an underscore.
//
// Example:
//   std::string name = "my file";
//   std::string safe = underscored(name);   // safe is "my_file", name is still "my file"
std::string underscored(std::string text) {
    for (char &c : text) {
        if (c == ' ') c = '_';
    }
    return text;
}

// Replace every 0 in values with fallback.
//
// Example:
//   values = {0, 3, 0}
//   replace_zeros(values, 9);   // values is now {9, 3, 9}
void replace_zeros(std::vector<int> &values, int fallback) {
    for (int &value : values) {
        if (value == 0) value = fallback;
    }
}

// Point selected at the first element equal to target.
// If no element equals target, set selected to nullptr.
//
// Example:
//   values = {4, 5, 5}
//   int *selected = nullptr;
//   select_first(values, 5, selected);   // selected == &values[1]
//   select_first(values, 9, selected);   // selected is nullptr
void select_first(std::vector<int> &values, int target, int *&selected) {
    selected = nullptr;
    for (int &value : values) {
        if (value == target) {
            selected = &value;
            return;
        }
    }
}

// Set to nullptr every slot that points at an int equal to target.
// Slots that are already nullptr stay that way, and the ints themselves don't change.
//
// Example:
//   int a = 1;
//   int b = 2;
//   slots = {&a, &b, nullptr, &a}
//   clear_matches(slots, 1);   // slots is now {nullptr, &b, nullptr, nullptr}, a is still 1
void clear_matches(std::vector<int *> &slots, int target) {
    for (int *&slot : slots) {
        if (slot && *slot == target) slot = nullptr;
    }
}

// Subtract amount from every element.
// The caller may pass one of values' own elements as amount.
//
// Example:
//   values = {5, 7, 9}
//   subtract_from_all(values, 2);           // values is now {3, 5, 7}
//   subtract_from_all(values, values[0]);   // values is now {0, 2, 4}
void subtract_from_all(std::vector<int> &values, const int &amount) {
    int originalAmount = amount;

    for (int &value : values) {
        value -= originalAmount;
    }
}

// Return a pointer to the largest element of values.
// If several elements tie for largest, point at the first one. values is never empty.
//
// Example:
//   values = {3, 8, 1, 8}
//   int *top = largest(values);   // top == &values[1]
//   *top = 0;                     // values is now {3, 0, 1, 8}
int *largest(std::vector<int> &values) {
    std::size_t best = 0;
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (values[i] > values[best]) best = i;
    }
    return &values[best];
}
