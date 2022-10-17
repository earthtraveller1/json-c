// This file contains the implementations for all of the public functions in
// this library. Of course, as the library grows it might be split into many o-
// ther files.

#include <stdlib.h>

#include <json/json.h>

#include "file-utils.h"
#include "json.h"
#include "parser.h"

struct json_object json_parse_file(const char *p_filepath, uint8_t *p_status)
{
    struct json_object result = {0, NULL};

    char *file_contents = read_file_as_string(p_filepath);
    if (file_contents == NULL)
    {
        *p_status = 0;
        return result;
    }

    uint32_t token_count;
    char **tokens = tokenize_string(file_contents, &token_count);

    result = json_parse_object_from_tokens((const char **)tokens, token_count,
                                           p_status);
    return result;
}

void json_free_object(struct json_object *p_object)
{
    for (uint32_t i = 0; i < p_object->field_count; i++)
    {
        free((void *)(p_object->fields[i].name));
        p_object->fields[i].name = NULL;

        if (p_object->fields[i].type == JSON_FIELD_TYPE_STRING)
        {
            free((void *)(p_object->fields[i].value.string_value));
        }
        else if (p_object->fields[i].type == JSON_FIELD_TYPE_OBJECT)
        {
            json_free_object(&(p_object->fields[i].value.object_value));
        }
        else if (p_object->fields[i].type == JSON_FIELD_TYPE_ARRAY)
        {
            json_free_array(&(p_object->fields[i].value.array_value));
        }
    }

    free(p_object->fields);
}

void json_free_array(struct json_array *p_array)
{
    for (uint32_t i = 0; i < p_array->element_count; i++)
    {
        if (p_array->elements[i].type == JSON_FIELD_TYPE_STRING)
        {
            free(p_array->elements[i].value.string_value);
        }
        else if (p_array->elements[i].type == JSON_FIELD_TYPE_OBJECT)
        {
            json_free_object(&(p_array->elements[i].value.object_value));
        }
        else if (p_array->elements[i].type == JSON_FIELD_TYPE_ARRAY)
        {
            json_free_array(&(p_array->elements[i].value.array_value));
        }
    }

    free(p_array->elements);
}
