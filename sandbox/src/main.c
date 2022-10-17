#include <json/json.h>

#include <stdio.h>

static void print_object(const struct json_object *p_object, uint8_t p_indents);

static void print_array(const struct json_array *p_array, uint8_t p_indents);

static void print_json_value(union json_field_value p_value,
                             enum json_field_type p_type, int8_t p_indents)
{
    switch (p_type)
    {
    case JSON_FIELD_TYPE_BOOLEAN:
        if (p_value.boolean_value)
        {
            puts("<BOOLEAN: true>");
        }
        else
        {
            puts("<BOOLEAN: false>");
        }
        break;
    case JSON_FIELD_TYPE_INTEGER:
        printf("<INTEGER: %d>\n", p_value.int_value);
        break;
    case JSON_FIELD_TYPE_FLOAT:
        printf("<FLOAT: %f>\n", p_value.float_value);
        break;
    case JSON_FIELD_TYPE_STRING:
        printf("%s\n", p_value.string_value);
        break;
    case JSON_FIELD_TYPE_OBJECT:
        puts("<OBJECT> with fields:");
        print_object(&(p_value.object_value), p_indents + 1);
        break;
    case JSON_FIELD_TYPE_ARRAY:
        puts("<ARRAY> with elements:");
        print_array(&(p_value.array_value), p_indents + 1);
        break;
    default:
        puts("<UNSUPPORTED TYPE>");
    }
}

static void print_object(const struct json_object *p_object, uint8_t p_indents)
{
    for (const struct json_field *field = p_object->fields;
         field < p_object->fields + p_object->field_count; field++)
    {
        for (uint8_t i = 0; i < p_indents; i++)
        {
            putchar('\t');
        }

        printf("%s = ", field->name);
        print_json_value(field->value, field->type, p_indents);
    }
}

static void print_array(const struct json_array *p_array, uint8_t p_indents)
{
    for (const struct json_array_element *element = p_array->elements;
         element < p_array->elements + p_array->element_count; element++)
    {
        for (uint8_t i = 0; i < p_indents; i++)
        {
            putchar('\t');
        }
        
        print_json_value(element->value, element->type, p_indents);
    }
}

int main()
{
    uint8_t status = 0;
    struct json_object object = json_parse_file("sandbox/tony.json", &status);

    puts("The object of 'sandbox/tony.json':");
    print_object(&object, 1);
}
