#include <string.h>

void* memmove(void* dest, const void* src, size_t n) {
    unsigned char* buf_dest = (unsigned char*)dest;
    const unsigned char* buf_src = (const unsigned char*)src;
    if (buf_dest < buf_src) {
        // dest may overlap the start of src, so copy from beginning
        for (size_t i=0; i<n; ++i) {
            buf_dest[i] = buf_src[i];
        }
    } else {
        // dest may overlap the end of src, so copy from the end
        for (size_t i=n-1; i>0; --i) {
            buf_dest[i] = buf_src[i];
        }
    }
    return (void*)buf_dest;
}
