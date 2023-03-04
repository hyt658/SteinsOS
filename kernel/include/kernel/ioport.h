#ifndef _IO_PORT_H_
#define _IO_PORT_H_

#include <stdint.h>

/*
Function name: oub
Description: assembly output value to I/O port
Parameters:
    @port: the output I/O port
    @val: the output value
Return: void
*/
static inline void 
outb(uint16_t port, uint8_t val) 
{
    __asm__ volatile ("outb %0, %1\n\t"
                        : /* no output */
                        : "a"(val), "d"(port)
                        : /* no registers modified */);
}

/*
Function name: inb
Description: assembly get input from I/O port
Parameters:
    @port: the I/O port to get input
    @result: the variable to store input
Return: void
*/
static inline void
inb(uint16_t port, uint8_t* result)
{
    __asm__ volatile ("inb %1, %0"
                        : "=a"(*result)
                        : "d"(port)
                        : /* no registers modified */);
}

#endif
