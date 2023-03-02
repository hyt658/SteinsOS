#include <string.h>

void* 
memchr(const void *buffer, int c, size_t n) 
{
    const unsigned char* buf = (const unsigned char*)buffer;
    for (size_t i=0; i<n; ++i) {
        if (*buf == (unsigned char)c) {
            return (void*)buf;
        }
        buf += 1;
    }
    return NULL;
}
