#ifndef EA82C1F4_C7D1_4128_B602_FDA1103EF91D
#define EA82C1F4_C7D1_4128_B602_FDA1103EF91D

#include <stdint.h>
#include <stddef.h>

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
    size_t field_count;
    struct json_field *fields;
};

struct json_array
{
    size_t element_count;
    struct json_array_element *elements;
};

union json_field_value
{
    uint8_t boolean_value;
    int32_t int_value;
    double float_value;
    char *string_value;
    struct json_object object_value;
    struct json_array array_value;
};

struct json_field
{
    char *name;
    enum json_field_type type;
    union json_field_value value;
};

struct json_array_element
{
    enum json_field_type type;
    union json_field_value value;
};

void json_free_object(struct json_object *object);

void json_free_array(struct json_array *array);

struct json_object json_parse_file(const char* filepath, uint8_t* status);

#endif /* EA82C1F4_C7D1_4128_B602_FDA1103EF91D */
