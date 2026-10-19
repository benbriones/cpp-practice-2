// Challenge: Inventory
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
// Grade: grade 04_structs_enums/04_inventory
// Try it: grade --run 04_structs_enums/04_inventory

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
