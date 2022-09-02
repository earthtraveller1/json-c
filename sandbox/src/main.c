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
    free((void *)file_contents);

    uint32_t symbol_count;
    const char **symbols =
        chunk_tokens_to_symbols(tokens, token_count, &symbol_count);
    free_string_array(tokens, token_count);
    
    printf("[INFO]: Symbols:\n");
    for (uint32_t i = 0; i < symbol_count; i++)
    {
        printf("\t%s\n", symbols[i]);
    }
    
    uint8_t status;
    struct json_object json_object = json_parse_object(symbols, symbol_count, &status);
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
        else 
        {
            printf("<NOT STRING>\n"); // Sorry, too lazy
        }
    }

    return 0;
}
