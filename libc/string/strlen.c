#include <string.h>

size_t 
strlen(const char *str) 
{
    size_t count = 0;
    while (*str != '\0') {
        count += 1;
        str += 1;
    }
    return count;
}
