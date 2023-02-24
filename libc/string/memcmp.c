#include <string.h>

int memcmp(const void *buffer1, const void *buffer2, size_t n) {
    const unsigned char* buf1 = (const unsigned char*)buffer1;
    const unsigned char* buf2 = (const unsigned char*)buffer2;
    for (size_t i=0; i<n; ++i) {
        if (*buf1 < *buf2) {
            return -1;
        } else if (*buf1 > *buf2) {
            return 1;
        }
        buf1 += 1;
        buf2 += 1;
    }
    return 0;
}
