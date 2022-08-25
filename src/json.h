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
    JSON_FIELD_TYPE_INT = 0,
    JSON_FIELD_TYPE_FLOAT = 1,
    JSON_FIELD_TYPE_STRING = 2,
    JSON_FIELD_TYPE_OBJECT = 3,
    JSON_FIELD_TYPE_ARRAY = 4
};

struct json_field
{
    const char *name;
    enum json_field_type type;
    void *value;
};

struct json_object
{
    size_t number_of_fields;
    struct json_field *fields;
};

struct json_array_element
{
    enum json_field_type type;
    void *value;
};

struct json_array
{
    size_t number_of_elements;
    struct json_array_element *elements;
};

struct json_object json_parse_object(const char** tokens, uint32_t token_count);

#endif /* D000424B_64A5_449A_BB64_37EE58E7F6F5 */
