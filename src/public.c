// This file contains the implementations for all of the public functions in 
// this library. Of course, as the library grows it might be split into many o-
// ther files.

#include <stdlib.h>

#include <json/json.h>

void json_free_object(struct json_object *p_object)
{
    for (uint32_t i = 0; i < p_object->number_of_fields; i++)
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
    for (uint32_t i = 0; i < p_array->number_of_elements; i++)
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
