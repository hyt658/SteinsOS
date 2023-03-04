#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <kernel/tty.h>

/*
Function name: print_number
Description: print out an integer number
Parameters:
    @num: the output integer number
    @digit: number of digits of this number
Return: void
*/
static void 
print_number(int num, unsigned int digit) 
{
    if (digit == 0) { return; }

    unsigned int base = (unsigned int)pow(10, digit-1);
    char output = num/base + '0';
    putchar(output);
    print_number(num%base, digit-1);
}


int 
printf(const char* format, ...) 
{
    va_list valist;
    va_start(valist, format);
    size_t len = 0;
    int written = 0;

    while (format[0] != '\0') {
        if (format[0] == '%') {
            if (format[1] == '%') {     /* %% prints out % */
                char ch = format[1];
                len = 1;
                putchar(ch);
            } else if (format[1] == 'c') {      /* %c for char */
                char ch = (char)va_arg(valist, int);
                len = sizeof(ch); 
                putchar(ch);     
            } else if (format[1] == 's') {      /* %s for string */
                const char* content = (const char*)va_arg(valist, int);
                len = strlen(content);
                terminal_output_string(content);
            } else if (format[1] == 'd') {      /* %d for int */
                int num = va_arg(valist, int);
                int temp = num;
                len = 1;
                while (temp / 10 != 0) { 
                    temp /= 10;
                    len += 1; 
                }
                if (num < 0) { putchar('-'); }
                print_number(num, len);
            }
            // TODO: finish all printf format
            format += 2;
        } else {
            char ch = format[0];
            len = 1;
            putchar(ch);
            format += 1;
        }
        written += len;
    }
    
    return len;
}
