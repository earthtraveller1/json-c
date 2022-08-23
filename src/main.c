#include <stdio.h>
#include <stdlib.h>

#include "file-utils.h"
#include "parser.h"

int main()
{
    char const* file_contents = read_file_as_string("sandbox/test.txt");
    if (!file_contents)
    {
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
    
    free_tokenized_string(tokens, token_amount);
    free((void*)file_contents);
    
    return 0;
}