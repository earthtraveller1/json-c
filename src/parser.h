#ifndef D8A5C875_09EB_4FC5_BE90_E1F17C80DFCC
#define D8A5C875_09EB_4FC5_BE90_E1F17C80DFCC

#include <stdint.h>

// A set of functions for parsing strings.

// Tokenize a string.
const char **tokenize_string(const char *string, uint32_t *token_count);

// Chunk a list of tokens into symbols
const char **chunk_tokens_to_symbols(const char **tokens, uint32_t token_count,
                                    uint32_t *symbol_count);

// Free an array of strings.
void free_string_array(const char **tokens, uint32_t token_count);

#endif /* D8A5C875_09EB_4FC5_BE90_E1F17C80DFCC */
