#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_WHITESPACE(string, i)                                               \
    (string[i] == ' ' || string[i] == '\t' || string[i] == '\n')

const char **tokenize_string(const char *p_string, uint32_t *p_token_count)
{
    *p_token_count = 0;

    // Get the number of tokens in the string.
    for (uint32_t i = 0; i < strlen(p_string); i++)
    {
        if (((i > 0) && !IS_WHITESPACE(p_string, i) &&
             IS_WHITESPACE(p_string, i - 1)) ||
            ((i > 0) && isalnum(p_string[i]) && !isalnum(p_string[i - 1])) ||
            ((i == 0) && !IS_WHITESPACE(p_string, i)) ||
            (!isalnum(p_string[i]) && !IS_WHITESPACE(p_string, i)))
        {
            *p_token_count += 1;
        }
    }

    char **tokens = malloc((*p_token_count) * sizeof(char *));

    uint32_t character_index = 0;
    for (uint32_t i = 0; i < *p_token_count; i++)
    {
        // Get the size of the token.
        uint32_t token_size = 0;
        {
            // Iterate until the next non-whitespace character.
            while (IS_WHITESPACE(p_string, character_index))
            {
                character_index++;
            }

            if (!isalnum(p_string[character_index]) &&
                !IS_WHITESPACE(p_string, character_index))
            {
                token_size = 1;
            }
            else
            {
                uint32_t counter_character_index = character_index;

                while (!IS_WHITESPACE(p_string, counter_character_index) &&
                       p_string[counter_character_index] != 0 &&
                       isalnum(p_string[counter_character_index]))
                {
                    token_size++;
                    counter_character_index++;
                }
            }
        }

        char *token = malloc(token_size + 1);
        token[token_size] = 0;

        memcpy(token, p_string + character_index, token_size);
        tokens[i] = token;
        character_index += token_size;
    }

    return (const char **)tokens;
}

const char **chunk_tokens_to_symbols(const char **p_tokens,
                                     uint32_t p_token_count,
                                     uint32_t *p_symbol_count)
{
    *p_symbol_count = 0;

    uint8_t is_in_string = 0;

    // First, obtain the number of symbols within the token list.
    for (uint32_t i = 0; i < p_token_count; i++)
    {
        if (strcmp(p_tokens[i], "\"") == 0)
        {
            if (is_in_string)
            {
                (*p_symbol_count)++;
                is_in_string = 0;
            }
            else
            {
                is_in_string = 1;
            }
        }
        else
        {
            (*p_symbol_count)++;
        }
    }

    // Next, we allocate the buffer to hold all the symbols.
    char **symbols = malloc((*p_symbol_count) * sizeof(char *));

    uint32_t token_index = 0;

    // Iterate through all the symbols.
    for (uint32_t i = 0; i < *p_symbol_count; i++)
    {
        char *symbol = NULL;
        
        // Prevent segmentation faults
        if (token_index >= p_token_count)
        {
            break;
        }

        if (strcmp(p_tokens[token_index], "\"") == 0)
        {
            uint32_t tokens_in_symbol = 0;
            {
                // We start counting from the token that's not a quotation
                uint32_t counter_token_index = token_index + 1;

                while ((counter_token_index < p_token_count) && (strcmp(p_tokens[counter_token_index], "\"") != 0))
                {
                    counter_token_index += 1;
                    tokens_in_symbol += 1;
                }

                // We must add two to include the beginning and ending quotati-
                // on marks.
                tokens_in_symbol += 1;
            }

            // Obtain the length of the symbol in bytes
            uint32_t symbol_length = 0;
            for (uint32_t i = 0; i < tokens_in_symbol; i++)
            {
                symbol_length += strlen(p_tokens[token_index + i]);
            }

            // Add one for the null terminator
            symbol_length += 1;

            symbol = malloc(symbol_length * sizeof(char));
            strcpy(symbol, p_tokens[token_index]);

            for (uint32_t i = 1; i < tokens_in_symbol; i++)
            {
                strcat(symbol, p_tokens[token_index + i]);
            }
            
            token_index += tokens_in_symbol;
        }
        else
        {
            uint32_t symbol_length = strlen(p_tokens[token_index]);
            symbol = malloc(symbol_length * sizeof(char));
            strcpy(symbol, p_tokens[token_index]);
            token_index++;
        }

        symbols[i] = symbol;
    }

    return (const char **)symbols;
}

void free_string_array(const char **p_tokens, uint32_t p_token_count)
{
    for (uint32_t i = 0; i < p_token_count; i++)
    {
        free((void *)p_tokens[i]);
    }

    free(p_tokens);
}
