#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include "vga.h"

/*
Function name: terminal_initialize
Description: initialize the terminal for output
Parameters: void
Return: void
*/
void terminal_initialize(void);

/*
Function name: terminal_clear
Description: clear the entire terminal
Parameters: void
Return: void
*/
void terminal_clear(void);

/*
Function name: terminal_change_color
Description: change the terminal color for future output
Parameters:
    @fg: foreground color
    @bg: background color
Return: void
*/
void terminal_change_color(enum vga_color fg, enum vga_color bg);

/*
Function name: terminal_output_char
Description: print a single char on the terminal
Parameters:
    @ch: the output char
    @is_str: 
        0 indicates currently only print a single char
        1 indicates currently is printing a string
Return: void
*/
void terminal_output_char(char ch, int is_str);

/*
Funtion name: terminal_output_string
Description: print a string on the terminal
Parameters:
    @data: the output string
Return: void
*/
void terminal_output_string(const char* data) ;

#endif
