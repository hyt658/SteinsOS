#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include "vga.h"

/**
 * @brief initialize the terminal for output
 * 
 * @return void
 */
void terminal_initialize(void);

/**
 * @brief clear the entire terminal
 * 
 * @return void
 */
void terminal_clear(void);

/**
 * @brief change the terminal color for future output
 * 
 * @param[in] fg: the foreground color wanted to change
 * @param[in] bg: the background color wanted to change
 * 
 * @return void
 */
void terminal_change_color(enum vga_color fg, enum vga_color bg);

/**
 * @brief print a single char on the terminal
 * 
 * @param[in] ch: char wanted to print
 * 
 * @return void
 */
void terminal_print_char(char ch);

/**
 * @brief print a string on the terminal
 * 
 * @param[in] str: the string wanted to print
 * 
 * @return void
 */
void terminal_print_string(const char* str);

#endif
