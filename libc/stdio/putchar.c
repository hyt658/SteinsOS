#include <stdio.h>
#include <kernel/tty.h>

int putchar(int ch) {
    char output = (char)ch;
    terminal_output_char(output, 0);
    return ch;
}
