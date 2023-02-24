#ifndef _STDIO_H_
#define _STDIO_H_

#include <stddef.h>

#define EOF (-1)

int printf(const char* fromat, ...);
int putchar(int ch);
int puts(const char* str);

#endif