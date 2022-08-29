#include <file-utils.h>
#include <json.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* file_contents = read_file_as_string("sandbox/tony.json");
    
    uint32_t token_count;
    const char** tokens = tokenize_string(file_contents, &token_count);
    free((void*)file_contents);
    
    uint32_t symbol_count;
    const char** symbols = chunk_tokens_to_symbols(tokens, token_count, &symbol_count);
    free_string_array(tokens, token_count);
    
    struct json_object json_object = json_parse_object(symbols, symbol_count);
    
    printf("Number of fields: %ld", json_object.number_of_fields);
    
    return 0;
}
