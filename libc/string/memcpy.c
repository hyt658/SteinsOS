#include <string.h>

void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* buf_dest = (unsigned char*)dest;
    const unsigned char* buf_src = (const unsigned char*)src;
    for (size_t i=0; i<n; ++i) {
        buf_dest[i] = buf_src[i];
    }
    return (void*)buf_dest;
}
