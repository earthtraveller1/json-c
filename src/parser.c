#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define IS_WHITESPACE(string, i) (string[i] == ' ' || string[i] == '\t' || string[i] == '\n')

const char **tokenize_string(const char *string, uint32_t *token_count)
{
    *token_count = 0;

    // Get the number of tokens in the string.
    for (uint32_t i = 0; i < strlen(string); i++)
    {
        if (i > 0 && !IS_WHITESPACE(string, i) && IS_WHITESPACE(string, i - 1))
        {
            *token_count += 1;
        }
    }

    char **tokens = malloc((*token_count) * sizeof(char *));

    uint32_t character_index = 0;
    for (uint32_t i = 0; i < *token_count; i++)
    {
        // Get the size of the token.
        uint32_t token_size = 0;
        {
            // Iterate until the next non-whitespace character.
            while (IS_WHITESPACE(string, character_index))
            {
                character_index++;
            }
            
            uint32_t counter_character_index = character_index;
            
            while (!IS_WHITESPACE(string, counter_character_index) && string[counter_character_index] != 0)
            {
                token_size++;
                counter_character_index++;
            }
        }
        
        char* token = malloc(token_size + 1);
        token[token_size] = 0;
        
        memcpy(token, string + character_index, token_size);
        tokens[i] = token;
        character_index += token_size;
    }

    return tokens;
}