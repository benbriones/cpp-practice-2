// === Lesson: Returning references ============================================
//
// A function that returns a reference hands back the box itself, not a copy of
// what's in it. The caller can read it, assign to it, or keep a name for it:
//
//     int &last(std::vector<int> &v) { return v.back(); }
//
//     last(v) = 0;              // writes the last element
//     ++last(v);                // so does this
//
// What the caller ends up with depends on the variable they put it in:
//
//     int copy = last(v);       // a copy: changing copy leaves v alone
//     int &same = last(v);      // another name for the element
//     auto a = last(v);         // auto drops the &, so this is a copy too
//     auto &b = last(v);        // auto& keeps it: another name for the element
//
// Range-for makes the same choice, one element at a time:
//
//     for (int x : v) x = 0;                  // zeroes copies; v is unchanged
//     for (int &x : v) x = 0;                 // zeroes v
//     for (const std::string &s : names) {}   // reads each string without copying it
//
// Return a reference only to a box that outlives the call: a reference
// parameter, or an element of one. A local is destroyed at the closing brace,
// so a reference to it dangles (03_references_pointers/05_lifetime_bugs). A
// const& return lets the caller read a big object without copying it:
//
//     const std::string &shortest(const std::vector<std::string> &words);
//
// Pointer or reference? Return a pointer when the answer might be "none"
// (nullptr), and a reference when there is always an answer.
//
// It's fine to return a reference into a vector, but the caller mustn't hold it
// across anything that grows the vector:
//
//     int &r = last(v);
//     v.push_back(9);           // may move every element to a new block
//     r = 1;                    // undefined behavior: r names freed memory
//
// Negative remainders. In C++, -1 % 5 is -1, not 4: the result of % takes the
// sign of the left side. ((i % n) + n) % n always lands between 0 and n - 1.
//
// Read more: https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
//            https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/
//
// === Exercise: Returning references ==========================================
// Predict the trace, then implement the five functions.
//
// ./grade 03b_more_references_pointers/05_returning_references

#include <cstddef>
#include <string>
#include <vector>

// Trace 7. What does v hold at the end?
//
//     std::vector<int> v{1, 2, 3};
//     int &first = v[0];
//     auto copy = v[1];
//     auto &alias = v[2];
//     first = 10;
//     copy = 20;
//     alias = 30;
//     int &again = first;
//     again += 5;
std::vector<int> trace_7() { return {15, 2, 30}; }

// Clamp every element into [lo, hi] in place.
// Values below lo become lo, values above hi become hi.
// Values already within the range stay unchanged.
//
// Example:
//   values = {2, 5, 10, 15, 20}
//   clamp_all(values, 5, 15);
//   values is now {5, 5, 10, 15, 15}
//
// Modifies the original vector; does not return anything.
void clamp_all(std::vector<int> &values, int lo, int hi) {
    for (int &v : values) {
        if (v > hi) {
            v = hi;
        } else if (v < lo) {
            v = lo;
        }
    }
}

// Return a reference to whichever variable has the larger value.
// If both values are equal, return a reference to a.
//
// Example:
//   int x = 10;
//   int y = 20;
//   max_ref(x, y) = 0;
//   // x is still 10, y is now 0.
//
// Since the function returns a reference, assigning to its result
// modifies the original variable, not a copy.

int &max_ref(int &a, int &b) {
    if (a == b) return a;

    if (a > b) return a;

    return b;
}

// Return a reference to the longest word in words.
// If several words tie for longest, return the first one.
// words is never empty.
//
// Example:
//   words = {"hi", "there", "you"}
//   const std::string &w = longest(words);
//   // w is "there", and &w == &words[1].
//
// Returns a const reference, so the caller reads the word without copying it.
const std::string &longest(const std::vector<std::string> &words) {
    std::size_t currMaxSize = 0;
    const std::string *currMaxValue  = &words[0];

    for (const std::string &w : words) {
        if (w.size() > currMaxSize) {
            currMaxSize = w.size();
            currMaxValue = &w;
        }
    }

    return *currMaxValue;
}

// Return a reference to the element at index, counting like Python.
// Negative indexes count from the end: -1 is the last element, -2 the one before.
// Indexes past either end wrap around. values is never empty.
//
// Example:
//   values = {10, 20, 30}
//   at_wrapped(values, -1) is 30, at_wrapped(values, 3) is 10
//   at_wrapped(values, 4) is 20, at_wrapped(values, -4) is 30
//   at_wrapped(values, -1) = 0;   // values is now {10, 20, 0}
//
// Since the function returns a reference, assigning to its result changes the vector.
int &at_wrapped(std::vector<int> &values, int index) { throw "TODO"; }

// Return a reference to name's count.
// names[i]'s count is counts[i], and the two vectors are always the same size.
// If name isn't in names yet, add it with a count of 0 first.
//
// Example:
//   names = {"ada"}, counts = {3}
//   ++count_for(names, counts, "ada");   // counts is now {4}
//   ++count_for(names, counts, "bob");   // names is {"ada", "bob"}, counts is {4, 1}
//
// Since the function returns a reference, ++ on its result updates counts directly.
int &count_for(std::vector<std::string> &names, std::vector<int> &counts, const std::string &name) {
    throw "TODO";
}
