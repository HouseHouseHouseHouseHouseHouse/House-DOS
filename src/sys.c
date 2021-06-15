#include <stdbool.h>

#include "inc/gdt.h"
#include "inc/serial.h"

/* DATA */
char *string = "House-DOS PHIL v0.2\r\n";

/* INIT */
void init(void)
{
    // Initialize GDT
    gdt_auto();

    // Initialize Serial
    serial_init(COM1);

    // Wait for Input
    serial_in(COM1);
}


/* MAIN */
void main(void)
{
    // Initialize
    init();

    // Output welcome string
    serial_outString(COM1, string);

    // Echo back input
    while (true) serial_out(COM1, serial_in(COM1));
}
