#include <string.h>

#include "json.h"

static uint32_t get_object_field_count(const char **p_tokens,
                                       uint32_t p_token_count)
{
    uint32_t result = 0;
    
    // TODO: Write this function.
    
    return result;
}

struct json_object json_parse_object(const char **p_tokens,
                                     uint32_t p_token_count)
{
    struct json_object result;
    result.fields = NULL;
    result.number_of_fields = 0;
    
    // TODO: Write this function
    
    return result;
}
