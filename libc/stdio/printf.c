#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

/*
Function name: print
Description: print out a string
Parameters:
    @output: output string
    @length: length of the output string
Return:
    0 means print properly
    1 means there is error during print
*/
static int 
print(const char* output, size_t length) 
{
    for (size_t i=0; i<length; ++i) {
        if (putchar(output[i]) == EOF) {
            return 1;
        }
    }
    return 0;
}

/*
Function name: print_number
Description: print out an integer number
Parameters:
    @num: the output integer number
    @digit: number of digits of this number
Return: void
*/
static int 
print_number(int num, unsigned int digit) 
{
    if (digit == 0) { return 0; }

    unsigned int base = (unsigned int)pow(10, digit-1);
    char output = num/base + '0';
    int error = print(&output, 1);
    
    if (error) { 
        return 1; 
    } else {
        return print_number(num%base, digit-1);
    } 
}


int 
printf(const char* format, ...) 
{
    va_list valist;
    va_start(valist, format);
    size_t len = 0;
    int written = 0;
    int error = 0;

    while (format[0] != '\0') {
        if (format[0] == '%') {
            if (format[1] == '%') {     /* %% prints out % */
                len = sizeof(format[1]);
                error = print(format+1, len);
            } else if (format[1] == 'c') {      /* %c for char */
                const char ch = (const char)va_arg(valist, int);
                len = sizeof(ch); 
                error = print(&ch, len);     
            } else if (format[1] == 's') {      /* %s for string */
                const char* content = (const char*)va_arg(valist, int);
                len = strlen(content);
                error = print(content, len);
            } else if (format[1] == 'd') {      /* %d for int */
                int num = va_arg(valist, int);
                int temp = num;
                len = 1;
                while (temp / 10 != 0) { 
                    temp /= 10;
                    len += 1; 
                }
                if (num < 0) { print("-", 1); }
                error = print_number(num, len);
            }
            // TODO: finish all printf format
            format += 2;
        } else {
            len = sizeof(format[0]);
            print(format, len);
            format += 1;
        }
        written += len;

        if (error) {
            // TODO: printf error
            break;
        }
    }
    
    return len;
}
