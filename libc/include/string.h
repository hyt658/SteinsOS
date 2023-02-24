#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

void* memchr(const void* buffer, int c, size_t n);
int memcmp(const void* buffer1, const void* buffer2, size_t n);
void* memcpy(void* dest, const void* src, size_t n);
void* memmove(void* dest, const void* src, size_t n);
void* memset(void* buffer, int c, size_t n);
char* strcpy(char *dest, const char *src);
size_t strlen(const char *str);

#endif
