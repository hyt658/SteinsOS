#include <string.h>

void* memset(void* buffer, int c, size_t n) {
    unsigned char* buf = (unsigned char*)buffer;
    for (size_t i=0; i<n; ++i) {
        buf[i] = (unsigned char)c;
    }
    return (void*)buf;
}
