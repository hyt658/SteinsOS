#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

#include <stdint.h>

/* Hardcoded 4-bit color codes. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

/* 
VGA text mode text buffer pattern (total 16 bits):
    1. bit 0-7: ASCII code
    2. bit 8-11: foreground color
    3. bit 12-14: background color
    4. bit 15: blink
*/

/*
Function name: vga_entry_color
Description: calculate the color section for VGA text buffer
Parameters:
    @fg: foreground color
    @bg: background color
Return: uint8_t color section for VGA text buffer
*/
static inline uint8_t 
vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | (bg << 4);
}
 
/*
 Function name: vga_entry
 Description: calculate the porper VGA text buffer and ready to write in
 Parameters:
    @ch: the char that is wanted to output
    @color: the foreground + background color of output
Return: uint16_t VGA text buffer
*/
static inline uint16_t 
vga_entry(unsigned char ch, uint8_t color) 
{
	return (uint16_t)ch | (uint16_t)color << 8;
}

#endif
