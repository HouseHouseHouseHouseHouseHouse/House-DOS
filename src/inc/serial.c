#include <stddef.h>

#include "serial.h"
#include "io.h"

/* SERIAL FUNCTIONS */

// Initialize serial port
int serial_init(uint16_t port)
{
    outb(port + 1, 0x00);               // Disable interrupts

    outb(port + 3, 0x80);               // Enable DLAB (set baud)
    outb(port + 0, 0x0C);               // Low byte of divisor
    outb(port + 1, 0x00);               // High byte of divisor     - 9600 baud

    outb(port + 3, 0x03);               // 8-bit chars, 1 stop bit, no parity

    outb(port + 2, 0xC7);               // Enable FIFO
    outb(port + 4, 0x0B);               // Enable IRQs

    outb(port + 4, 0x1E);               // Loopback mode
    outb(port + 0, 0xAA);               // Test serial chip

    // If we don't receive correctly, error
    if (inb(port) != 0xAA) return -1;

    // Otherwise, normal operation
    outb(port + 4, 0x0F);
    return 0;
}

// Retrieve input from a serial port
char serial_in(uint16_t port)
{
    // Wait to receive a byte, then return it
    while ((inb(port + 5) & 0x01) == 0);
    return inb(port);
}

void serial_out(uint16_t port, char data)
{
    // Wait for transmission buffer to open, then send
    while ((inb(port + 5) & 0x20) == 0);
    outb(port, data);
}

void serial_outString(uint16_t port, char *str)
{
    for (size_t i = 0; str[i] != 0x00; i++) serial_out(port, str[i]);
}
