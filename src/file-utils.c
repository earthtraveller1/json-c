#include <stdint.h>
#include <stdio.h>

uint32_t get_file_size(FILE* p_file)
{
    fseek(p_file, 0, SEEK_SET);
    
    uint32_t result = 0;
    
    while(fgetc(p_file) != EOF)
    {
        result++;
    }
    
    return result;
}