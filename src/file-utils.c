#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

const char* read_file_as_string(const char* p_filename)
{
    FILE* file = fopen(p_filename, "r");
    if (!file)
    {
        return NULL;
    }
    
    uint32_t buffer_length = get_file_size(file) + 1;
    char* buffer = malloc((buffer_length) * sizeof(char));
    
    fseek(file, 0, SEEK_SET);
    fgets(buffer, buffer_length, file);
    
    fclose(file);
    
    return buffer;
}
