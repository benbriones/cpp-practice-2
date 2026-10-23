# C++ Practice 2

A self-paced, exercise-driven course in modern C++ (C++20) with a command-line autograder.
You learn by writing code: open an exercise, read its short lesson, write C++, run `grade`, repeat.

## Getting started

You need a C++ compiler and Python 3.9+. On macOS: `xcode-select --install`, then check
`c++ --version` and `python3 --version`.

Make `grade` work from anywhere by adding this to `~/.zshrc` (or run `./grade` from this folder):

```sh
alias grade="$HOME/Projects/Personal/cpp-practice-2/grade"
```

Then:

1. Open [src/01_basics/01_arithmetic.cpp](src/01_basics/01_arithmetic.cpp).
2. Read the lesson at the top of the file, then the exercise instructions under it.
3. Replace each `throw "TODO";` with your code.
4. Run `grade 01/01`.
5. Fix what fails. When everything passes, `grade` tells you which exercise is next.

## The `grade` command

| Command                         | What it does                                                                                             |
| ------------------------------- | -------------------------------------------------------------------------------------------------------- |
| `grade 01_basics/01_arithmetic` | Grade one exercise. `grade 1/1`, `grade basics/arithmetic`, or a path to the `.cpp` also work.           |
| `grade 03`                      | Summary of every exercise in module 03.                                                                  |
| `grade --all`                   | Progress through the whole course, plus the next exercise to do.                                         |
| `grade --run 01/05`             | Compile an exercise and run its own `main()` so you can try it by hand. Program arguments go after `--`. |
| `grade -v <exercise>`           | Also show the full compiler output and everything your code printed.                                     |

Test results: `✓` passed, `✗` failed (with expected vs. received, or what crashed and where),
`○` not implemented yet. Exercise status: `✓` complete, `◐` in progress, `○` not started,
`✗` compile error.

Anything your code prints to `std::cout` shows up under a failing test, so print-debugging works.

## How grading works

- Your file is compiled together with its tests (`tests/<module>/<exercise>.cpp`) using
  `-std=c++20 -Wall -Wextra -Wpedantic -Wshadow` with AddressSanitizer and
  UndefinedBehaviorSanitizer. Out-of-bounds access, use-after-free, dangling references, signed
  overflow and null dereferences are reported with the line in your file, instead of seeming
  to work.
- Each test runs in its own process with a 5-second limit, so a crash or an infinite loop only
  fails that test.
- Starter code always compiles. Unfinished parts `throw "TODO"`, which the grader reports as
  "not implemented" rather than failed. That's how it tells "not started" from "in progress".
- Exercises with a `main()` are run with the test's input on stdin, and their output is
  compared line by line (trailing whitespace is ignored).
- Compiler warnings from your file are listed after the results. They don't fail a test, but
  read them.
- Everything is built in a temporary directory. Nothing is written into the project.

## The course

Work through the modules in order; each one assumes the ones before it. Exercises within a
module go from easy to harder, and most modules end with a ★ challenge that combines topics.
Modules 03b and 03c are extra drill on references and pointers, right after 03. Module 19 is an
optional bonus you can slot in any time after module 04.

21 modules, 98 exercises, about 1050 tests.

| Module                                                                       | What you'll practise                                                                                                                                                                                                                | Exercises                                                                                                    |
| ---------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| [01 basics](src/01_basics)                                                   | Fundamental types, integer division and overflow, `static_cast`, operators, `if`/`switch`, loops, overloading, default arguments, recursion, `std::cin`/`std::cout`                                                                 | arithmetic, conditions, loops, functions, number report ★                                                    |
| [02 strings & vectors](src/02_strings_vectors)                               | `std::string`, `<cctype>`, `std::vector`, range-for, `size_t` pitfalls, `const&` parameters, 2D grids, `getline`, `istringstream`                                                                                                   | strings, vectors, split and join, grids, word count ★                                                        |
| [03 references & pointers](src/03_references_pointers)                       | References, out-parameters, pointers and `nullptr`, `const` pointers, `std::optional`, `std::string_view`, dangling references                                                                                                      | references, pointers, optional, string_view, lifetime bugs ★                                                 |
| [03b more references & pointers](src/03b_more_references_pointers)           | Memory-box diagrams, `x`/`&x`/`p`/`*p`, same value vs. same object, `p =` vs. `*p =`, predict-the-result traces, `nullptr` guards and "not found", `->`, optional out-parameters, `int*&`, returning references, `auto` vs. `auto&` | addresses, dereferencing, nullptr, parameters, returning references, pointer bugs ★                          |
| [03c even more references & pointers](src/03c_even_more_references_pointers) | Pass by value vs. `&` vs. `const&`, changing and returning a by-value copy, aliased parameters, what binds to `&` and `const&`, `int**` vs. `int*&`, pointers to containers, reading a signature                                    | pass by value, pass by reference, const references, pointer parameters, reading signatures, parameter bugs ★ |
| [04 structs & enums](src/04_structs_enums)                                   | Structs, designated initializers, `enum class`, vectors of records, `->`, `std::pair`, structured bindings                                                                                                                          | structs, enums, records, inventory ★                                                                         |
| [05 classes](src/05_classes)                                                 | Encapsulation, constructors and initializer lists, invariants, `const` and `static` members, `explicit`, composition                                                                                                                | counter, time of day, shopping cart, class bugs, library ★                                                   |
| [06 containers](src/06_containers)                                           | `std::map`, `std::set`, `unordered_map`/`unordered_set`, `std::array`, iterators and erase loops, `std::stack`, `std::queue`                                                                                                        | maps, sets, unordered_map, arrays and iterators, stacks and queues ★                                         |
| [07 algorithms & lambdas](src/07_algorithms_lambdas)                         | Lambdas and captures, `std::function`, function pointers, comparators, `<algorithm>`, `<numeric>`, erase-remove, ranges and views, `<random>`                                                                                       | lambdas, sorting, algorithms, erase and ranges, random, leaderboard ★                                        |
| [08 error handling](src/08_error_handling)                                   | `throw`/`try`/`catch`, standard exceptions, custom exception hierarchies, catch order, optional vs. out-parameter vs. exception                                                                                                     | exceptions, custom exceptions, error strategies, bank teller ★                                               |
| [09 streams & files](src/09_streams_files)                                   | String streams, stream state, `std::format`, `ifstream`/`ofstream`, append and binary modes, parsing CSV, `std::cerr`                                                                                                               | string streams, reading files, writing files, CSV report ★                                                   |
| [10 memory](src/10_memory)                                                   | C arrays and decay, pointer arithmetic, C strings, `new`/`delete`, linked lists, `std::span`, 2D arrays                                                                                                                             | C arrays, C strings, new and delete, span, dynamic array ★                                                   |
| [11 RAII & smart pointers](src/11_raii_smart_pointers)                       | Destructors, RAII, the rule of three, `std::unique_ptr`, `std::shared_ptr`/`std::weak_ptr`, ownership                                                                                                                               | scope guard, rule of three, unique_ptr, shared and weak, newsletter ★                                        |
| [12 move semantics](src/12_move_semantics)                                   | rvalues, `std::move`, move constructor and assignment, `noexcept`, the rules of five and zero, copy elision                                                                                                                         | copies and moves, rule of five, rule of zero, move bugs ★                                                    |
| [13 operator overloading](src/13_operator_overloading)                       | Arithmetic and comparison operators, `<=>`, `<<`, `[]`, `()`, conversion operators, function objects, custom hashes                                                                                                                 | fraction, vec2, matrix, functors and hashing ★                                                               |
| [14 inheritance & polymorphism](src/14_inheritance_polymorphism)             | Derived classes, `virtual`/`override`, abstract classes, virtual destructors, slicing, `dynamic_cast`, interfaces, `std::variant` + `std::visit`                                                                                    | accounts, shapes, polymorphism bugs, interfaces, variant shapes ★                                            |
| [15 templates](src/15_templates)                                             | Function and class templates, non-type parameters, CTAD, concepts, `if constexpr`, variadic templates, fold expressions                                                                                                             | function templates, class templates, concepts, variadic, sorted vector ★                                     |
| [16 multi-file programs](src/16_multi_file_programs)                         | Headers vs. source files, `#pragma once`, linker errors and the ODR, namespaces, internal linkage, templates in headers                                                                                                             | split into files, namespaces and linkage, classes and templates in headers, mini library ★                   |
| [17 concurrency](src/17_concurrency)                                         | `std::thread`/`jthread`, `std::mutex`, `scoped_lock`, `std::atomic`, `std::async`/`std::future`, `condition_variable`                                                                                                               | threads, mutex, atomic and async, blocking queue ★                                                           |
| [18 capstone projects](src/18_capstone_projects)                             | Everything together, in bigger multi-part programs                                                                                                                                                                                  | LRU cache ★, expression calculator ★, bank system ★, ASCII canvas ★                                          |
| [19 bonus: bit manipulation](src/19_bonus_bit_manipulation)                  | Bitwise operators, masks, flag enums, packing bytes, `std::bitset` (optional)                                                                                                                                                       | bitwise, permission flags, color packing ★                                                                   |

### Why this order

- **Useful programs early.** `std::string` and `std::vector` come in module 02, before pointers
  and classes, because they're what everyday C++ is written with.
- **References before raw memory.** You meet references, pointers, `std::optional` and
  `std::string_view` early (03), but C arrays, pointer arithmetic and `new`/`delete` wait until
  module 10, once you can write classes to manage them. Modules 10 → 11 → 12 then tell the
  ownership story in order: raw memory, RAII and smart pointers, move semantics.
- **Standard library before building your own.** Containers and algorithms (06–07) come before
  operator overloading and templates (13, 15), so you've used the library before you write
  types that behave like it.
- **Deferred on purpose.** Header/linkage details wait for module 16, when your programs are
  big enough to need them. Bit manipulation is an optional bonus. Not covered: C++20 modules,
  coroutines, template metaprogramming, locales, and most of the preprocessor.
- **Fix-the-bug exercises.** A few exercises hand you code that compiles but is wrong (dangling
  references, slicing, use-after-move), so they start out failing rather than "not started".
  Reading sanitizer reports is a core C++ skill. Three exercises in module 16 start out not
  even building: fixing the build is the exercise.

## Adding an exercise

1. Create `src/<module>/<NN_name>.cpp`: a `// === Lesson: ... ===` block of up to 60 lines (the
   concepts plus a short example on a different problem), a `// === Exercise: ... ===` block
   with the instructions, the `#include`s, and stubs whose bodies are `throw "TODO";`.
2. Create `tests/<module>/<NN_name>.cpp`:

   ```cpp
   #include "grader.hpp"
   #include "<module>/<NN_name>.cpp"

   TEST("square: positive numbers") {
       CHECK_EQ(square(3), 9);
   }

   PROGRAM_TEST("Echoes its input", { .input = "hi\n", .output = "hi\n" });
   ```

3. `grade <module>/<NN_name>` should now say "not started". To check the tests against a
   reference solution kept outside the repo, mirror `src/` somewhere else and run
   `grade <module>/<NN_name> --src path/to/solutions`.

Checks: `CHECK(condition)` or `CHECK(condition, "message")`, `CHECK_EQ(actual, expected)`,
`CHECK_NEAR(actual, expected[, tolerance])`, `CHECK_THROWS(ExceptionType, expression)`.
Helpers: `grader::capture_stdout`, `grader::write_file`, `grader::read_file` (each test runs in
its own empty temp directory). Exercises are discovered automatically, and the number prefix
sets the order (a letter suffix, as in `03b_`, slots a module in after `03_`). A folder instead of a `.cpp` file makes a multi-file exercise: every `.cpp` in
it is compiled and linked with the tests.

## Layout

```
grade                 the command (forwards to grader/grade.py)
grader/grade.py       finds, compiles and runs exercises; prints results
grader/grader.hpp     the test macros used by tests/
grader/runner.cpp     runs one test per process inside the compiled exercise
src/                  the exercises: one folder per module
tests/                the tests, mirroring src/
compile_flags.txt     the grader's flags, for clangd (editor autocomplete and errors)
```

Set `CXX` to use a different compiler (`CXX=clang++ grade 01/01`), and `GRADE_TIMEOUT` to change
the 5-second limit per test on a slow machine.
