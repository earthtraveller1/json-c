#ifndef D8A5C875_09EB_4FC5_BE90_E1F17C80DFCC
#define D8A5C875_09EB_4FC5_BE90_E1F17C80DFCC

#include <stdint.h>

// A set of functions for parsing strings.

// Tokenize a string.
char **tokenize_string(const char *string, uint32_t *token_count);

// Free an array of strings.
void free_string_array(char **strings, uint32_t string_count);

#endif /* D8A5C875_09EB_4FC5_BE90_E1F17C80DFCC */
