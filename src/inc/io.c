#include "io.h"

/* I/O FUNCTIONS */

// Output byte to port
inline void outb(uint16_t port, uint8_t x)
{
    asm volatile ( "outb %0, %1"
        :
        : "a"(x), "Nd"(port)
    );
}

// Get byte of input from port
inline uint8_t inb(uint16_t port)
{
    uint8_t x;

    asm volatile ( "inb %1, %0"
        : "=a"(x)
        : "Nd"(port)
    );

    return x;
}
