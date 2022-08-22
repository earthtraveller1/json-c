#include <stdio.h>
#include <stdlib.h>

#include "file-utils.h"

int main()
{
    char const* file_contents = read_file_as_string("sandbox/test.txt");
    if (!file_contents)
    {
        fprintf(stderr, "[FATAL ERROR]: Failed to find or load sandbox/test.txt\n");
        return EXIT_FAILURE;
    }
    
    printf("File Content:\n%s\n", file_contents);
    
    file_contents = "Hello, yes!\n";
    
    free((void*)file_contents);
    
    return 0;
}