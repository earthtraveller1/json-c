#include <stdio.h>
#include <stdlib.h>

#include "file-utils.h"
#include "parser.h"

const char **tokenize_file(const char *p_filename, uint32_t *token_count)
{
    const char *file_contents = read_file_as_string(p_filename);
    if (file_contents == NULL)
    {
        return NULL;
    }

    printf("File Contents:\n%s", file_contents);

    const char **tokens = tokenize_string(file_contents, token_count);
    free((void *)file_contents);

    return tokens;
}

int main()
{
    uint32_t token_count;
    const char **tokens = tokenize_file("sandbox/tony.json", &token_count);

    printf("\nTokens:\n");
    for (uint32_t i = 0; i < token_count; i++)
    {
        printf("\t%s\n", tokens[i]);
    }
    
    uint32_t symbol_count;
    const char** symbols = chunk_tokens_to_symbols(tokens, token_count, &symbol_count);
    free_string_array(tokens, token_count);
    
    printf("\nSymbols:\n");
    for (uint32_t i = 0; i < symbol_count; i++)
    {
        printf("\t%s\n", symbols[i]);
    }
    
    free_string_array(symbols, symbol_count);

    return 0;
}
