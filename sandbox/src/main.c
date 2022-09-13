#include <file-utils.h>
#include <json.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char *file_contents = read_file_as_string("sandbox/tony.json");

    uint32_t token_count;
    const char **tokens = tokenize_string(file_contents, &token_count);
    
    printf("[INFO]: Tokens:\n");
    for (uint32_t i = 0; i < token_count; i++)
    {
        printf("\t%s\n", tokens[i]);
    }
    
    free((void *)file_contents);
    
    uint8_t status;
    struct json_object json_object = json_parse_object(tokens, token_count, &status);
    if (!status)
    {
        fprintf(stderr, "[ERROR]: Failed to parse JSON 'sandbox/tony.json'\n");
        return -1;
    }

    printf("[INFO]: Number of fields: %zd\n", json_object.number_of_fields);
    
    printf("[INFO]: Field names and values:\n");
    for (uint32_t i = 0; i < json_object.number_of_fields; i++)
    {
        printf("\t%s = ", json_object.fields[i].name);
        if (json_object.fields[i].type == JSON_FIELD_TYPE_STRING)
        {
            printf("%s\n", json_object.fields[i].value.string_value);
        }
        else if (json_object.fields[i].type == JSON_FIELD_TYPE_OBJECT)
        {
            printf("\n");
            for (uint32_t j = 0; j < json_object.fields[i].value.object_value.number_of_fields; j++)
            {
                printf("\t\t%s = ", json_object.fields[i].value.object_value.fields[j].name);
                
                if (json_object.fields[i].value.object_value.fields[j].type == JSON_FIELD_TYPE_STRING)
                {
                    printf("%s\n", json_object.fields[i].value.object_value.fields[j].value.string_value);
                }
                else 
                {
                    printf("<VALUE HERE>\n");
                }
            }
        }
        else 
        {
            printf("<VALUE HERE>\n"); // Sorry, too lazy
        }
    }
    
    json_free_object(&json_object);

    return 0;
}
