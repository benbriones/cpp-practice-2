// === Lesson: Bugs that compile ===============================================
//
// The compiler checks that types line up, not that you changed the box you
// meant to. Each of these compiles, most of them without a warning, and then
// quietly changes the wrong thing or nothing at all:
//
// 1. Assigning the pointer instead of the box. Inside a function, a pointer
//    parameter p is the function's own copy of an address. p = &x re-points
//    that copy and the caller never sees it; *p = x writes the caller's box.
//
// 2. Copying when you meant to alias. int x = v[0], auto x = f() and
//    for (int x : v) all make copies, and writing to a copy changes nothing
//    else. Use int&, auto& or for (int &x : v) to change the original.
//
// 3. Expecting a reference to move. int &r = a; r = b; doesn't make r name b:
//    it copies b's value into a. To track "the best element so far" in a loop,
//    use a pointer or an index, which can move.
//
// 4. Testing the wrong thing. if (p) asks "does p point somewhere?", and if (*p)
//    asks "is the int it points at nonzero?". *p on a nullptr crashes, so the
//    first question has to come before the second.
//
// 5. Precedence. *p++ moves p and leaves the int alone; ++*p or (*p)++ adds 1
//    to the int.
//
// Read grade's warnings after the results: "set but not used" often means a
// write went to a copy, and "expression result unused" often points at *p++.
//
// Each fix is small: usually adding, removing or moving a * or an &. If a fix
// takes a rewrite, look again.
//
// Read more: https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/
//
// === Challenge: Pointer and reference bugs ===================================
// Every function below compiles and looks reasonable, but seven of them have a
// pointer or reference bug. Run grade, read what fails, and fix all seven. Keep
// each function's name, parameters and return type.
//
// ./grade 03b_more_references_pointers/06_pointer_bugs

#include <cstddef>
#include <vector>

// Exchange the two ints that a and b point at.
//
// Example:
//   int x = 1;
//   int y = 2;
//   swap_values(&x, &y);
//   // x is now 2, y is now 1
void swap_values(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Add bonus to every score.
// bonus may be negative.
//
// Example:
//   scores = {70, 85, 90}
//   add_bonus(scores, 5);
//   // scores is now {75, 90, 95}
void add_bonus(std::vector<int> &scores, int bonus) {
    for (int &score : scores) {
        score += bonus;
    }
}

// Write how many elements are negative into *count_out.
// 0 is not negative. count_out is never null.
//
// Example:
//   int count = -1;
//   count_negatives({3, -1, 0, -7, 2}, &count);
//   // count is now 2
void count_negatives(const std::vector<int> &values, int *count_out) {
    int count = 0;
    for (int value : values) {
        if (value < 0) ++count;
    }
    *count_out = count;
}

// Set the largest element to 0.
// If several elements tie for largest, zero only the first one.
// values is never empty.
//
// Example:
//   values = {4, 9, 9}
//   zero_largest(values);
//   // values is now {4, 0, 9}
void zero_largest(std::vector<int> &values) {
    int *best = &values[0];
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (values[i] > *best) best = &values[i]; 
    }
    *best = 0;
}

// Return how many slots hold a pointer.
// nullptr slots are empty. A slot pointing at a 0 still counts.
//
// Example:
//   int zero = 0;
//   int five = 5;
//   count_filled({&zero, nullptr, &five}) is 2
int count_filled(const std::vector<const int *> &slots) {
    int count = 0;
    for (const int *slot : slots) {
        if (slot) ++count;
    }
    return count;
}

// Add 1 to every int the pointers point at, skipping nullptrs.
// A pointer that appears twice gets 1 added twice.
//
// Example:
//   int x = 0;
//   int y = 10;
//   bump_all({&x, nullptr, &y, &x});
//   // x is now 2, y is now 11
void bump_all(const std::vector<int *> &counters) {
    for (int *p : counters) {
        if (p) (*p)++;
    }
}

// Return a reference to the largest age.
// If several ages tie for largest, return the first one.
// This one has no bug.
//
// Example:
//   ages = {30, 72, 45, 72}
//   &oldest(ages) == &ages[1]   // the first 72
int &oldest(std::vector<int> &ages) {
    std::size_t best = 0;
    for (std::size_t i = 1; i < ages.size(); ++i) {
        if (ages[i] > ages[best]) best = i;
    }
    return ages[best];
}

// Add one year to the oldest age.
// If several ages tie for oldest, only the first one gets older.
// ages is never empty.
//
// Example:
//   ages = {30, 72, 45}
//   birthday_for_oldest(ages);
//   // ages is now {30, 73, 45}
void birthday_for_oldest(std::vector<int> &ages) {
    auto &age = oldest(ages);
    age += 1;
}
