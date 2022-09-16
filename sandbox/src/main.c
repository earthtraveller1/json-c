#include <file-utils.h>
#include <json.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>

static void print_array(const struct json_array *p_array, uint8_t p_indents);

#define PRINT_INDENTS(indents, i)                                              \
    /* NOLINTNEXTLINE */                                                       \
    for (uint8_t i = 0; i < (indents); i++)                                    \
    {                                                                          \
        putc('\t', stdout);                                                    \
    }

static void print_object(const struct json_object *p_object, uint8_t p_indents)
{
    for (uint32_t i = 0; i < p_object->number_of_fields; ++i)
    {
        PRINT_INDENTS(p_indents, j)
        printf("%s = ", p_object->fields[i].name);

// NOLINTNEXTLINE
#define IF_FIELD_TYPE_IS(t) if (p_object->fields[i].type == t)

        IF_FIELD_TYPE_IS(JSON_FIELD_TYPE_STRING)
        {
            printf("%s\n", p_object->fields[i].value.string_value);
        }
        else IF_FIELD_TYPE_IS(JSON_FIELD_TYPE_OBJECT)
        {
            printf("Object with values:\n");
            print_object(&(p_object->fields[i].value.object_value),
                         p_indents + 1);
        }
        else IF_FIELD_TYPE_IS(JSON_FIELD_TYPE_ARRAY)
        {
            printf("Array [%zu]\n",
                   p_object->fields[i].value.array_value.number_of_elements);
            print_array(&(p_object->fields[i].value.array_value), p_indents + 1);
        }
        else
        {
            printf("<UNSUPPORTED TYPE>\n");
        }

#undef IF_FIELD_TYPE_IS
    }
}

static void print_array(const struct json_array *p_array, uint8_t p_indents)
{
    for (uint32_t i = 0; i < p_array->number_of_elements; i++)
    {
        PRINT_INDENTS(p_indents, j)

// NOLINTNEXTLINE
#define IF_ELEMENT_TYPE_IS(t) if (p_array->elements[i].type == t)

        IF_ELEMENT_TYPE_IS(JSON_FIELD_TYPE_STRING)
        {
            printf("%s\n", p_array->elements[i].value.string_value);
        }
        else IF_ELEMENT_TYPE_IS(JSON_FIELD_TYPE_OBJECT)
        {
            printf("Object with values:\n");
            print_object(&(p_array->elements[i].value.object_value),
                         p_indents + 1);
        }
        else IF_ELEMENT_TYPE_IS(JSON_FIELD_TYPE_ARRAY)
        {
            printf("Array [%zu]\n",
                   p_array->elements[i].value.array_value.number_of_elements);
            print_array(&(p_array->elements[i].value.array_value),
                        p_indents + 1);
        }
        else
        {
            printf("<UNSUPPORTED TYPE>\n");
        }

#undef IF_ELEMENT_TYPE_IS
    }
}

int main()
{
    const char *file_contents = read_file_as_string("sandbox/tony.json");

    uint32_t token_count;
    const char **tokens = tokenize_string(file_contents, &token_count);

    free((void *)file_contents);

    uint8_t status;
    struct json_object json_object =
        json_parse_object(tokens, token_count, &status);
    if (!status)
    {
        fprintf(stderr, "[ERROR]: Failed to parse JSON 'sandbox/tony.json'\n");
        return -1;
    }

    printf("[INFO]: Number of fields: %zd\n", json_object.number_of_fields);

    printf("[INFO]: Field names and values:\n");
    print_object(&json_object, 1);

    json_free_object(&json_object);

    return 0;
}
