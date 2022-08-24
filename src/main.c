#include <stdio.h>
#include <stdlib.h>

#include "file-utils.h"
#include "parser.h"

const char** tokenize_file(const char* p_filename, uint32_t* token_count)
{
    const char* file_contents = read_file_as_string(p_filename);
    if (file_contents == NULL)
    {
        return NULL;
    }
    
    printf("File Contents:\n%s", file_contents);
    
    const char** tokens = tokenize_string(file_contents, token_count);
    
    return tokens;
}

int main()
{
    uint32_t token_count;
    const char** tokens = tokenize_file("sandbox/tony.json", &token_count);
    
    printf("\nTokens:\n");
    for (uint32_t i = 0; i < token_count; i++)
    {
        printf("\t%s\n", tokens[i]);
    }
    
    free_tokenized_string(tokens, token_count);
    
    return 0;
}
