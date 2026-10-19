#include "grader.hpp"
#include "05_classes/05_library.cpp"

static Library sample() {
    Library library;
    library.add_book("Dune", "Herbert");
    library.add_book("Emma", "Austen");
    library.add_book("Persuasion", "Austen");
    library.add_book("Neuromancer", "Gibson");
    return library;
}

TEST("add_book: new titles go on the shelf") {
    Library library;
    CHECK_EQ(library.size(), 0);
    CHECK_EQ(library.add_book("Dune", "Herbert"), true);
    CHECK_EQ(library.size(), 1);
    CHECK_EQ(library.is_available("Dune"), true);
}

TEST("add_book: duplicate titles are rejected") {
    Library library = sample();
    CHECK_EQ(library.add_book("Dune", "Someone Else"), false);
    CHECK_EQ(library.size(), 4);
    CHECK_EQ(library.books_by("Someone Else"), {});
}

TEST("is_available: unknown titles are not available") {
    Library library = sample();
    CHECK_EQ(library.is_available("Ulysses"), false);
}

TEST("checkout: lends an available book") {
    Library library = sample();
    CHECK_EQ(library.checkout("Emma", "ada"), true);
    CHECK_EQ(library.is_available("Emma"), false);
    CHECK_EQ(library.available_count(), 3);
    CHECK_EQ(library.size(), 4);
}

TEST("checkout: fails for unknown or already-lent books") {
    Library library = sample();
    CHECK_EQ(library.checkout("Ulysses", "ada"), false);
    CHECK_EQ(library.checkout("Emma", "ada"), true);
    CHECK_EQ(library.checkout("Emma", "grace"), false);
    CHECK_EQ(library.loans_of("grace"), {});
}

TEST("checkout: a member holds at most kMaxLoans books") {
    Library library = sample();
    CHECK_EQ(library.checkout("Dune", "ada"), true);
    CHECK_EQ(library.checkout("Emma", "ada"), true);
    CHECK_EQ(library.checkout("Persuasion", "ada"), true);
    CHECK_EQ(library.checkout("Neuromancer", "ada"), false);
    CHECK_EQ(library.is_available("Neuromancer"), true);
    CHECK_EQ(library.checkout("Neuromancer", "grace"), true);
}

TEST("return_book: puts the book back on the shelf") {
    Library library = sample();
    library.checkout("Dune", "ada");
    CHECK_EQ(library.return_book("Dune"), true);
    CHECK_EQ(library.is_available("Dune"), true);
    CHECK_EQ(library.loans_of("ada"), {});
    CHECK_EQ(library.checkout("Dune", "grace"), true);
}

TEST("return_book: fails for unknown or shelved books") {
    Library library = sample();
    CHECK_EQ(library.return_book("Dune"), false);
    CHECK_EQ(library.return_book("Ulysses"), false);
}

TEST("return_book: frees up a loan slot") {
    Library library = sample();
    library.checkout("Dune", "ada");
    library.checkout("Emma", "ada");
    library.checkout("Persuasion", "ada");
    library.return_book("Emma");
    CHECK_EQ(library.checkout("Neuromancer", "ada"), true);
}

TEST("books_by: in the order they were added") {
    Library library = sample();
    CHECK_EQ(library.books_by("Austen"), {"Emma", "Persuasion"});
    CHECK_EQ(library.books_by("Gibson"), {"Neuromancer"});
    CHECK_EQ(library.books_by("Nobody"), {});
}

TEST("books_by: includes books that are lent out") {
    Library library = sample();
    library.checkout("Emma", "ada");
    CHECK_EQ(library.books_by("Austen"), {"Emma", "Persuasion"});
}

TEST("loans_of: in library order, per member") {
    Library library = sample();
    library.checkout("Neuromancer", "ada");
    library.checkout("Dune", "ada");
    library.checkout("Emma", "grace");
    CHECK_EQ(library.loans_of("ada"), {"Dune", "Neuromancer"});
    CHECK_EQ(library.loans_of("grace"), {"Emma"});
    CHECK_EQ(library.loans_of("nobody"), {});
}

TEST("const Library can be queried") {
    Library library = sample();
    library.checkout("Dune", "ada");
    const Library& view = library;
    CHECK_EQ(view.available_count(), 3);
    CHECK_EQ(view.size(), 4);
    CHECK_EQ(view.is_available("Emma"), true);
}
