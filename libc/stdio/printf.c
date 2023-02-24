#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// return 1 means error
static int print(const char* output, size_t length) {
    for (size_t i=0; i<length; ++i) {
        if (putchar(output[i]) == EOF) {
            return 1;
        }
    }
    return 0;
}

int printf(const char* format, ...) {
    va_list valist;
    va_start(valist, format);
    size_t len = 0;
    const char* content = NULL;
    int written = 0;

    while (format[0] != '\0') {
        if (format[0] == '%') {
            if (format[1] == '%') {
                content = format + 1;
                len = sizeof(format[1]);
            } else if (format[1] == 'c') {
                const char ch = (const char)va_arg(valist, int);
                content = &ch;
                len = sizeof(ch);      
            } else if (format[1] == 's') {
                content = va_arg(valist, const char*);
                len = strlen(content);
            }
            // TODO: finish all printf format
            format += 2;
        } else {
            content = format;
            len = sizeof(format[0]);
            format += 1;
        }

        print(content, len);
        written += len;
    }
    
    return len;
}
