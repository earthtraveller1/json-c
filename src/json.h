#ifndef D000424B_64A5_449A_BB64_37EE58E7F6F5
#define D000424B_64A5_449A_BB64_37EE58E7F6F5

/*
A list of functions and structures used for decoding JSON files. Note that none
of them have actually been implemented yet so I would avoid using them whenever
possible. Most of them should be self explanatory.
*/

#include <stddef.h>
#include <stdint.h>

enum json_field_type
{
    JSON_FIELD_TYPE_BOOLEAN = 0,
    JSON_FIELD_TYPE_INTEGER = 1,
    JSON_FIELD_TYPE_FLOAT = 2,
    JSON_FIELD_TYPE_STRING = 3,
    JSON_FIELD_TYPE_OBJECT = 4,
    JSON_FIELD_TYPE_ARRAY = 5
};

struct json_object
{
    size_t number_of_fields;
    struct json_field *fields;
};

struct json_array
{
    size_t number_of_elements;
    struct json_array_element *elements;
};

union json_field_value
{
    uint8_t boolean_value;
    int32_t int_value;
    double float_value;
    const char *string_value;
    struct json_object object_value;
    struct json_array array_value;
};

struct json_field
{
    const char *name;
    enum json_field_type type;
    union json_field_value value;
};

struct json_array_element
{
    enum json_field_type type;
    union json_field_value value;
};

struct json_object json_parse_object(const char **tokens, uint32_t token_count, uint8_t* status);

#endif /* D000424B_64A5_449A_BB64_37EE58E7F6F5 */
