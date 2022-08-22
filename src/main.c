#include <stdio.h>
#include <stdlib.h>

#include "file-utils.h"
#include "parser.h"

int main()
{
    char const* file_contents = read_file_as_string("sandbox/test.txt");
    if (!file_contents)
    {
        fprintf(stderr, "[FATAL ERROR]: Failed to find or load sandbox/test.txt\n");
        return EXIT_FAILURE;
    }
    
    printf("File Content:\n%s\n", file_contents);
    printf("Tokens:\n");
    
    uint32_t token_amount;
    const char** tokens = tokenize_string(file_contents, &token_amount);
    
    for (uint32_t i = 0; i < token_amount; i++)
    {
        printf("\t%s\n", tokens[i]);
    }
    
    free((void*)file_contents);
    
    return 0;
}