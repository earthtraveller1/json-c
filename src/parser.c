#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define IS_WHITESPACE(string, i) (string[i] == ' ' || string[i] == '\t' || string[i] == '\n')

const char **tokenize_string(const char *p_string, uint32_t *p_token_count)
{
    *p_token_count = 0;

    // Get the number of tokens in the string.
    for (uint32_t i = 0; i < strlen(p_string); i++)
    {
        if (
            ((i > 0) && !IS_WHITESPACE(p_string, i) && IS_WHITESPACE(p_string, i - 1)) ||
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

            if (!isalnum(p_string[character_index]) && !IS_WHITESPACE(p_string, character_index))
            {
                token_size = 1;
            }
            else
            {
                uint32_t counter_character_index = character_index;

                while (
                    !IS_WHITESPACE(p_string, counter_character_index) &&
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

void free_tokenized_string(const char **p_tokens, uint32_t p_token_count)
{
    for (uint32_t i = 0; i < p_token_count; i++)
    {
        free((void *)p_tokens[i]);
    }

    free(p_tokens);
}
