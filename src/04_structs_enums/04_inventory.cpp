// === Lesson: A command-driven program ========================================
//
// Many small programs read commands one line at a time. Read whole lines, then
// split each one into words with a string stream:
//
//     std::string line;
//     while (std::getline(std::cin, line)) {       // false once input runs out
//         std::istringstream words(line);          // from <sstream>
//         std::string command, target, amount;
//         words >> command >> target >> amount;    // each >> reads one word
//         if (command.empty()) continue;           // a blank line
//         ...
//     }
//
// Reading into a std::string can't fail on odd text: a missing word just leaves
// the string empty. Reading straight into an int is less forgiving. On "x" it
// fails, stores 0 and puts the stream in a fail state where every later read
// fails too. On "1.5" it happily reads 1 and leaves ".5" behind. So careful
// programs read the text, check it, and only then convert it, for example with
// std::stoi from <string>.
//
// A switch can't take a std::string, so dispatch on the command word with an
// if / else if chain.
//
// Finding a record: a helper that returns a pointer to the matching element, or
// nullptr, lets the caller both test for it and update it:
//
//     Player* p = find_player(team, "ada");      // a helper you'd write
//     if (p == nullptr) { ... } else { p->score += 10; }
//
// That pointer points into the vector's storage. push_back may move every
// element to a new block, and erase shifts the elements after the erased one,
// so don't keep such a pointer across either. Look the item up again instead.
//
// Removing from the middle of a vector while keeping the order:
//
//     v.erase(v.begin() + i);       // removes v[i]; later elements move up one
//
// v.begin() is an iterator to the first element, and + i steps to element i.
// Module 06 covers iterators properly.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
//            https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/
//
// === Challenge: Inventory ====================================================
// Write a program that keeps a stock list. Read commands from standard input,
// one per line, until input ends:
//
//   add <item> <qty>       add qty units; a new item goes to the end of the list
//   remove <item> <qty>    take qty units away; an item that reaches 0 leaves the list
//   count <item>           print "<item>: <qty>"  (0 for an item not in stock)
//   list                   print "<item>: <qty>" for every item in list order,
//                          or "(empty)" when there are none
//
// Errors print one line and change nothing:
//   error: bad quantity 'x'          qty is missing, not all digits, or 0 (check this first)
//   error: no pear in stock          removing an item that isn't in the list
//   error: only 3 apple in stock     removing more than there is
//   error: unknown command 'sell'    any other command
// Blank lines are ignored, and so is anything after the expected words.
//
// Keep the items in a std::vector<Item>. Small helper functions keep main()
// readable, e.g. one that finds an item and returns an Item* or nullptr.
// Hint: read the quantity as a std::string first, then check and convert it.
//
// ./grade 04_structs_enums/04_inventory
// Try it: ./grade --run 04_structs_enums/04_inventory

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Item {
    std::string name;
    int quantity{};
};

int main() {
    throw "TODO";
}
