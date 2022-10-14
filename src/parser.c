#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_WHITESPACE(string, i)                                               \
    ((string)[i] == ' ' || (string)[i] == '\t' || (string)[i] == '\n')

char **tokenize_string(const char *p_string, uint32_t *p_token_count)
{
    *p_token_count = 0;

    uint8_t inside_string = 0;

    // Get the number of tokens in the string.
    for (uint32_t i = 0; i < strlen(p_string); i++)
    {
        if (inside_string)
        {
            if (p_string[i] == '"' && p_string[i - 1] != '\\')
            {
                inside_string = 0;
            }
        }
        else
        {
            if (p_string[i] == '"')
            {
                inside_string = 1;
                *p_token_count += 1;
            }
            else
            {
                if (((i > 0) && !IS_WHITESPACE(p_string, i) &&
                     IS_WHITESPACE(p_string, i - 1)) ||
                    ((i > 0) && isalnum(p_string[i]) &&
                     !isalnum(p_string[i - 1])) ||
                    ((i == 0) && !IS_WHITESPACE(p_string, i)) ||
                    (!isalnum(p_string[i]) && !IS_WHITESPACE(p_string, i)))
                {
                    *p_token_count += 1;
                }
            }
        }
    }

    if (*p_token_count == 0)
    {
        return NULL;
    }

    char** tokens = malloc((*p_token_count) * sizeof(char *));

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

            if (p_string[character_index] == '"')
            {
                uint32_t counter_character_index = character_index + 1;
                while (p_string[counter_character_index] != '"')
                {
                    token_size += 1;
                    counter_character_index += 1;
                }

                token_size += 2;
            }
            else
            {
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
        }

        char *token = malloc(token_size + 1);
        token[token_size] = 0;

        memcpy(token, p_string + character_index, token_size);
        // memcpy_s(token, token_size, p_string + character_index, token_size);
        tokens[i] = token;
        character_index += token_size;
    }

    return tokens;
}

void free_string_array(char **p_strings, uint32_t p_string_count)
{
    for (uint32_t i = 0; i < p_string_count; i++)
    {
        free(p_strings[i]);
    }

    free(p_strings);
}
