#ifndef D000424B_64A5_449A_BB64_37EE58E7F6F5
#define D000424B_64A5_449A_BB64_37EE58E7F6F5

enum json_field_type_e
{
    JSON_FIELD_TYPE_INT = 0,
    JSON_FIELD_TYPE_FLOAT = 1,
    JSON_FIELD_TYPE_STRING = 2,
    JSON_FIELD_TYPE_OBJECT = 3,
    JSON_FIELD_TYPE_ARRAY = 4
};

struct json_field_t
{
    const char* name;
    json_field_type_e type;
    void* value;
};

struct json_object_t
{
    size_t number_of_fields;
    json_field_t* fields;
};

struct json_array_element_t
{
    json_field_type_e type;
    void* value;
};

struct json_array_t
{
    size_t number_of_elements;
    json_array_element_t* elements;
};

#endif /* D000424B_64A5_449A_BB64_37EE58E7F6F5 */
