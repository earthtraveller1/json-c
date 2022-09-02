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
    
    // uint8_t status;
    // struct json_object json_object = json_parse_object(tokens, token_count, &status);
    // if (!status)
    // {
    //     fprintf(stderr, "[ERROR]: Failed to parse JSON 'sandbox/tony.json'\n");
    //     return -1;
    // }

    // printf("[INFO]: Number of fields: %zd\n", json_object.number_of_fields);
    
    // printf("[INFO]: Field names and values:\n");
    // for (uint32_t i = 0; i < json_object.number_of_fields; i++)
    // {
    //     printf("\t%s = ", json_object.fields[i].name);
    //     if (json_object.fields[i].type == JSON_FIELD_TYPE_STRING)
    //     {
    //         printf("%s\n", json_object.fields[i].value.string_value);
    //     }
    //     else 
    //     {
    //         printf("<NOT STRING>\n"); // Sorry, too lazy
    //     }
    // }

    return 0;
}
