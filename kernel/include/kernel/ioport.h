#ifndef _IO_PORT_H_
#define _IO_PORT_H_

#include <stdint.h>

/**
 * @brief assembly output value to I/O port
 * 
 * @param[in] port: I/O port wanted to output
 * @param[in] val: value wanted to output
 * 
 * @return void
 */
static inline void 
outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ("outb %0, %1"
                        : /* no output */
                        : "a"(val), "d"(port)
                        : /* no registers modified */);
}

/**
 * @brief assembly get input from I/O port
 * 
 * @param[in] port: I/O port that read from
 * @param[out] result: the value get from I/O port 
 * 
 * @return void
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
