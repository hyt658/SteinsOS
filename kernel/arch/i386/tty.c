#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/ioport.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

uint16_t* const VGA_MEMORY = (uint16_t*)0xB8000;
const uint16_t VGA_REGISTER_SELECT_PORT = 0x3D4;
const uint16_t VGA_REGISTER_ACCESS_PORT = 0x3D5;

const uint8_t VGA_CURSOR_START_REGISTER = 0x0A;
const uint8_t VGA_CURSOR_END_REGISTER = 0x0B;
const uint8_t VGA_CURSOR_POS_HIGH_REGISTER = 0x0E;
const uint8_t VGA_CURSOR_POS_LOW_REGISTER = 0x0F;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

/*
Function name: enable_cursor
Description: 
    enable the cursor on VGA text mode. By default the cursor will occupy the entire
    char block (fill in from scanline 0 to 16)
Parameters: void
Return: void
*/
static void 
enable_cursor(void)
{
    uint8_t result;

    uint8_t scanline_start_reset_mask = 0xC0;
    uint8_t scanline_end_rest_mask = 0xE0;
    uint8_t scanline_start = 0;
    uint8_t scanline_end = 15;

    outb(VGA_REGISTER_SELECT_PORT, VGA_CURSOR_START_REGISTER);
    inb(VGA_REGISTER_ACCESS_PORT, &result);
    outb(VGA_REGISTER_ACCESS_PORT, (result & scanline_start_reset_mask) | scanline_start);

    outb(VGA_REGISTER_SELECT_PORT, VGA_CURSOR_END_REGISTER);
    inb(VGA_REGISTER_ACCESS_PORT, &result);
    outb(VGA_REGISTER_ACCESS_PORT, (result & scanline_end_rest_mask) | scanline_end);
}

/*
Function name: disable_cursor
Description: disable the cursor on VGA text mode
Parameters: void
Return: void
*/
// static void 
// disable_cursor(void)
// {
//     uint8_t disable_value = 0x20;
// 	outb(VGA_REGISTER_SELECT_PORT, VGA_CURSOR_START_REGISTER);
// 	outb(VGA_REGISTER_ACCESS_PORT, disable_value);
// }

static void
update_cursor_pos(void)
{
    size_t idx = terminal_row * VGA_WIDTH + terminal_column;
    uint8_t low_eight_bits_mask = 0xFF;

    /* store high 8 bits in high register */
    outb(VGA_REGISTER_SELECT_PORT, VGA_CURSOR_POS_HIGH_REGISTER);
    outb(VGA_REGISTER_ACCESS_PORT, (uint8_t)((idx >> 8) & low_eight_bits_mask));

    /* store low 8 bits in low register */
    outb(VGA_REGISTER_SELECT_PORT, VGA_CURSOR_POS_LOW_REGISTER);
    outb(VGA_REGISTER_ACCESS_PORT, (uint8_t)(idx & low_eight_bits_mask));
}

static void
terminal_scroll_up(void) 
{
    // for each line, copy and store the content from next line
    for (size_t y=0; y<VGA_HEIGHT; ++y) {
        for (size_t x=0; x<VGA_WIDTH; ++x) {
            const size_t idx = y * VGA_WIDTH + x;
            
            terminal_buffer[idx] = terminal_buffer[idx + VGA_WIDTH];
        }
    }

    // clear the bottom line
    for (size_t x=0; x<VGA_WIDTH; ++x) {
        const size_t idx = (VGA_HEIGHT-1) * VGA_WIDTH + x;
        terminal_buffer[idx] = vga_entry(' ', terminal_color);
    }
}

void 
terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
    terminal_clear();
    enable_cursor();
    update_cursor_pos();
}

void 
terminal_clear(void) 
{
    for (size_t y=0; y<VGA_HEIGHT; ++y) {
		for (size_t x=0; x<VGA_WIDTH; ++x) {
			const size_t idx = y * VGA_WIDTH + x;
			terminal_buffer[idx] = vga_entry(' ', terminal_color);
		}
	}
    terminal_row = 0;
    terminal_column = 0;
    update_cursor_pos();
}
 
void 
terminal_change_color(enum vga_color fg, enum vga_color bg) 
{
    terminal_color = vga_entry_color(fg, bg);
}

void 
terminal_output_char(char ch, int is_str) 
{
    switch (ch) {
        
    case '\n':      /* newline */
        terminal_column = 0;
        terminal_row += 1;  
        break;

    case '\t':      /* tab */
        int count = (terminal_column + 4) / 4;
        terminal_column = count * 4;
        if (terminal_column == VGA_WIDTH) {
            terminal_column -= 4;
        }
        break;

    case '\r':      /* carriage return */
        terminal_column = 0;
        break;
        
    default:        /* normal output char */
        const size_t index = terminal_row * VGA_WIDTH + terminal_column;
        terminal_buffer[index] = vga_entry(ch, terminal_color);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_row += 1;
        }
    }

    if (terminal_row == VGA_HEIGHT) {
        terminal_scroll_up();
        terminal_row -= 1;
    }
    
    if (!is_str) { update_cursor_pos(); }
}
 
void 
terminal_output_string(const char* data) 
{
    size_t size = strlen(data);
    int is_str = 1;
	for (size_t i=0; i<size; ++i) {
        terminal_output_char(data[i], is_str);
    }
    update_cursor_pos();
}
