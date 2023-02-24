#include <string.h>

char* strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest += 1;
        src += 1;
    }
    return dest;
}
