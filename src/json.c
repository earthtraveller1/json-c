#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

static uint32_t get_block_size_in_symbols(const char **p_symbols,
                                          size_t p_starting_symbol,
                                          size_t p_symbol_count)
{
    const char opening_char = p_symbols[p_starting_symbol][0];
    char closing_char;
    if (opening_char == '{')
    {
        closing_char = '}';
    }
    else if (opening_char == '[')
    {
        closing_char = ']';
    }
    else
    {
        fprintf(stderr, "[ERROR]: Unknown block-opening character '%c'\n",
                opening_char);
    }

    uint32_t required_closing_chars_to_close = 1;

    uint32_t result = 1;

    for (uint32_t i = p_starting_symbol + 1; i < p_symbol_count; i++)
    {
        if (p_symbols[i][0] == opening_char)
        {
            required_closing_chars_to_close += 1;
        }

        if (p_symbols[i][0] == closing_char)
        {
            required_closing_chars_to_close -= 1;
        }

        if (required_closing_chars_to_close == 0)
        {
            break;
        }

        result += 1;
    }

    return result;
}

static uint32_t get_object_field_count(const char **p_symbols,
                                       uint32_t p_symbol_count)
{
    uint32_t result = 0;

    uint32_t required_closing_chars = 0;
    char closing_char = 0;

    for (uint32_t i = 0; i < p_symbol_count; i += 1)
    {
        const char *symbol = p_symbols[i];

        if (required_closing_chars == 0 && strcmp(symbol, ":") == 0)
        {
            result += 1;
        }
        else if (strcmp(symbol, "{") == 0 &&
                 (closing_char == '}' || closing_char == 0))
        {
            required_closing_chars += 1;
            closing_char = '}';
        }
        else if (strcmp(symbol, "[") == 0 &&
                 (closing_char == ']' || closing_char == 0))
        {
            required_closing_chars += 1;
            closing_char = ']';
        }
        else if (symbol[0] == closing_char && required_closing_chars != 0)
        {
            required_closing_chars -= 1;
        }

        if (required_closing_chars == 0)
        {
            closing_char = 0;
        }
    }

    return result;
}

struct json_object json_parse_object(const char **p_symbols,
                                     uint32_t p_symbol_count)
{
    struct json_object result;
    result.number_of_fields = get_object_field_count(
        p_symbols + 1,
        p_symbol_count - 1); // Exclude the beginning and ending braces
    result.fields = malloc(sizeof(struct json_field) * result.number_of_fields);

    uint32_t symbol_index = 0;
    uint32_t required_closing_chars = 0;
    char closing_char = 0;

    if (strcmp(p_symbols[0], "{") != 0)
    {
        fprintf(stderr, "[ERROR]: Object does not seem to start with '{'\n");
        return result; // TODO: Better error handling mechanism
    }

    for (uint32_t i = 0; i < result.number_of_fields; i++)
    {
        // Closing braces indicates the end of the object.
        if ((required_closing_chars == 0 || closing_char != '}') &&
            strcmp(p_symbols[symbol_index], "}") == 0)
        {
            break;
        }

        // Iterate until hitting a string symbol
        while (p_symbols[symbol_index][0] != '\"' &&
               p_symbols[symbol_index][strlen(p_symbols[symbol_index]) - 1] !=
                   '\"')
        {
            symbol_index += 1;
        }

        // Extract the name of the field
        const size_t name_size = strlen(p_symbols[symbol_index]) - 2;
        char *field_name = malloc((name_size + 1) * sizeof(char));
        strncpy(field_name, p_symbols[symbol_index] + 1, name_size);

        // Ensures that it will be null terminated
        field_name[name_size] = 0;

        symbol_index += 1;
        if (p_symbols[symbol_index][0] != ':')
        {
            fprintf(stderr, "[ERROR]: Expected ':' after field name of '%s'\n",
                    field_name);
            return result; // TODO: Better error handling mechanism
        }

        symbol_index += 1;

        union json_field_value field_value;
        enum json_field_type field_type;
        if (p_symbols[symbol_index][0] == '\"' &&
            p_symbols[symbol_index][strlen(p_symbols[symbol_index]) - 1] ==
                '\"')
        {
            field_type = JSON_FIELD_TYPE_STRING;
            const size_t field_size = strlen(p_symbols[symbol_index]) - 2;
            char *field_string_value = malloc((field_size + 1) * sizeof(char));
            strncpy(field_string_value, p_symbols[symbol_index] + 1,
                    field_size);

            field_value.string_value = field_string_value;
        }
        else if (strcmp(p_symbols[symbol_index], "true") == 0)
        {
            field_type = JSON_FIELD_TYPE_BOOLEAN;
            field_value.boolean_value = 1;
        }
        else if (strcmp(p_symbols[symbol_index], "false") == 0)
        {
            field_type = JSON_FIELD_TYPE_BOOLEAN;
            field_value.boolean_value = 0;
        }
        else if (p_symbols[symbol_index][0] == '{')
        {
            field_type = JSON_FIELD_TYPE_OBJECT;
            field_value.object_value = NULL; // TODO: Parse child objects

            symbol_index += get_block_size_in_symbols(p_symbols, symbol_index,
                                                      p_symbol_count);
        }
        else if (p_symbols[symbol_index][0] == '[')
        {
            field_type = JSON_FIELD_TYPE_ARRAY;
            field_value.array_value = NULL; // TODO: Parse arrays

            symbol_index += get_block_size_in_symbols(p_symbols, symbol_index,
                                                      p_symbol_count);
        }
        else
        {
            fprintf(stderr, "[ERROR]: Expected value at field '%s'\n",
                    field_name);
            return result; // TODO: Better error handling mechanism
        }

        symbol_index += 1;

        if (p_symbols[symbol_index][0] != ',' &&
            p_symbols[symbol_index][0] != '}')
        {
            fprintf(stderr, "[ERROR]: Expected ',' after field '%s'\n",
                    field_name);
            return result; // TODO: Better error handling mechanism
        }

        struct json_field field;
        field.name = field_name;
        field.type = field_type;
        field.value = field_value;

        result.fields[i] = field;
    }

    return result;
}
