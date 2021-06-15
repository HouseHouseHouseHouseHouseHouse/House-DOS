#include <stdint.h>

#ifndef IO_H
#define IO_H

// I/O Functions
void outb(uint16_t, uint8_t);
uint8_t inb(uint16_t);

#endif
