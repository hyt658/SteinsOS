#include <stdio.h>
#include <kernel/tty.h>

int putchar(int ch) {
    char output = (char)ch;
    terminal_putchar(output);
    return ch;
}
