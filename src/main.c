#include <stdio.h>

#include "file-utils.h"

int main()
{
    FILE* test_file = fopen("sandbox/test.txt", "r");
    if (test_file == NULL)
    {
        fprintf(stderr, "[FATAL ERROR]: Failed to open sandbox/test.txt\n");
    }
    
    const uint32_t file_size = get_file_size(test_file);
    
    printf("File size: %d\n", file_size);
    
    return 0;
}