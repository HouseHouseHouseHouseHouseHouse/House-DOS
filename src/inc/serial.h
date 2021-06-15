#include <stdint.h>

#ifndef SERIAL_H
#define SERIAL_H

// Serial I/O port numbers
#define COM1 0x03F8
#define COM2 0x02F8

// Serial functions
int serial_init(uint16_t);
char serial_in(uint16_t);
void serial_out(uint16_t, char);
void serial_outString(uint16_t, char*);

#endif
