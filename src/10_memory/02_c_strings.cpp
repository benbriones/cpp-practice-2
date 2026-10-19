// Exercise: C strings
// A C string is a char array ending in '\0':  "hi" is {'h', 'i', '\0'}.
// Its length isn't stored anywhere; you walk forward until the terminator.
// std::string is built on exactly this. Don't use <cstring>: you're writing it.
//
// ./grade 10_memory/02_c_strings

#include <cstddef>

// Number of characters before the '\0'.
std::size_t my_strlen(const char* s) {
    throw "TODO";
}

// Like std::strcmp: negative if a sorts before b, 0 if equal, positive if after.
// Only the sign matters. "app" sorts before "apple".
int my_strcmp(const char* a, const char* b) {
    throw "TODO";
}

// Copy src, including its '\0', into dest (which is big enough). Return dest.
char* my_strcpy(char* dest, const char* src) {
    throw "TODO";
}

// Pointer to the first c in s, or nullptr if s doesn't contain it.
const char* find_char(const char* s, char c) {
    throw "TODO";
}
