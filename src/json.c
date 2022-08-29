#include <string.h>

#include "json.h"

static uint32_t get_object_field_count(const char **p_symbols,
                                       uint32_t p_symbol_count)
{
    uint32_t result = 0;
    
    uint32_t required_closing_chars = 0;
    char closing_char = 0;
    
    for (uint32_t i = 0; i < p_symbol_count; i += 1)
    {
        const char* symbol = p_symbols[i];
        
        if (required_closing_chars == 0 && strcmp(symbol, ":") == 0)
        {
            result += 1;
        }
        else if (strcmp(symbol, "{") == 0 && (closing_char == '}' || closing_char == 0))
        {
            required_closing_chars += 1;
            closing_char = '}';
        }
        else if (strcmp(symbol, "[") == 0 && (closing_char == ']' || closing_char == 0))
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
    result.fields = NULL;
    result.number_of_fields = get_object_field_count(p_symbols + 1, p_symbol_count - 1); // Exclude the beginning and ending braces
    
    // TODO: Write this function
    
    return result;
}
