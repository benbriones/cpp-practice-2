// === Lesson: C strings =======================================================
//
// A C string is a char array whose end is marked by the character '\0' (the
// value 0). Its length isn't stored anywhere: code finds the end by walking
// forward until it meets the terminator.
//
//     char word[] = "hey";          // 4 chars: 'h', 'e', 'y', '\0'
//     sizeof("hello")               // 6: a literal includes its '\0'
//     const char *name = "Ada";     // points at a read-only literal
//
// A string literal has type const char[N]. You can read it through a
// const char*, but you can't change it: passing "hey" to a char* parameter is
// not allowed in C++ (clang warns), and writing to it crashes or worse. To get
// a modifiable copy, initialize a char array from the literal, as `word` above.
//
// Walking a C string. A pointer parameter is a copy of the caller's pointer, so
// you can advance it freely; the caller's pointer doesn't move:
//
//     // Replace every space with '_', in place.
//     void underscore(char *s) {
//         for (; *s != '\0'; ++s) {
//             if (*s == ' ') *s = '_';
//         }
//     }
//     char title[] = "hello big world";
//     underscore(title);            // "hello_big_world"
//
// chars are small integers: 'a' < 'b' compares their codes, and in ASCII every
// upper-case letter comes before every lower-case one ('Z' < 'a'). '\0' is 0,
// smaller than any printable character.
//
// Writing into a buffer. Whoever writes a C string must also write its '\0';
// without it, the next reader runs off the end. And the destination must be big
// enough: C strings never grow, and writing past the end of the array is
// undefined behavior. That mistake, the buffer overflow, is behind a long list
// of security holes, and the reason C++ code prefers std::string.
//
// Returning a pointer into the string, or nullptr for "not there", is how the C
// library reports positions. const-ness carries through: from a const char* you
// can only hand back a const char*.
//
// Mixing with std::string: std::string s = "hi"; copies from a C string, and
// s.c_str() gives a const char* to its text, '\0' included.
//
// Read more: https://www.learncpp.com/cpp-tutorial/c-style-strings/
//
// === Exercise: C strings =====================================================
// Don't use <cstring>: you're writing your own versions of its functions.
//
// ./grade 10_memory/02_c_strings

#include <cstddef>

// Return the number of characters before the '\0'.
// The '\0' itself isn't counted, and anything after the first '\0' is ignored.
//
// Example:
//   my_strlen("hello") == 5
//   my_strlen("") == 0
//
// The length isn't stored anywhere, so walk forward until you meet the '\0'.
std::size_t my_strlen(const char *s) {
    throw "TODO";
}

// Compare a and b like std::strcmp does.
// Return a negative number if a sorts before b, 0 if equal, positive if after.
// Only the sign matters. A prefix sorts before the longer string: "app" < "apple".
//
// Example:
//   my_strcmp("apple", "apple") == 0
//   my_strcmp("apple", "banana") < 0
//   my_strcmp("banana", "apple") > 0
//   my_strcmp("app", "apple") < 0
int my_strcmp(const char *a, const char *b) {
    throw "TODO";
}

// Copy src, including its '\0', into dest, and return dest.
// dest is always big enough to hold src.
// Characters in dest after the copied '\0' are left as they were.
//
// Example:
//   char buffer[16];
//   my_strcpy(buffer, "hello") == buffer
//   // buffer now starts with 'h', 'e', 'l', 'l', 'o', '\0'
//
// Without the '\0', dest has no end, and the next reader runs off it.
char *my_strcpy(char *dest, const char *src) {
    throw "TODO";
}

// Return a pointer to the first c in s.
// Return nullptr if s doesn't contain c. An empty string contains nothing.
//
// Example:
//   const char *text = "hello world";
//   find_char(text, 'o') == text + 4
//   find_char(text, 'z') == nullptr
//
// The result points into s itself, so it's a const char* like s.
const char *find_char(const char *s, char c) {
    throw "TODO";
}
