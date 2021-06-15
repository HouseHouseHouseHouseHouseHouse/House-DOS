#include "gdt.h"

// GDT Buffer
static uint8_t buffer [0x18];

/* GDT Functions */

// Encode GDT Entry
void gdt_encode(uint8_t *dest, struct GDT_Entry source)
{
    // Check if we need page granularity, set up flags
    if (source.limit > 0xFFFF) {
        source.limit >>= 0x0C;
        dest[6] = 0xC0;
    } else {
        dest[6] = 0x40;
    }

    // Encode Limit
    dest[0] = (source.limit >> 0x00) & 0xFF;
    dest[1] = (source.limit >> 0x08) & 0xFF;
    dest[6] |= (source.limit >> 0x10) & 0x0F;

    // Encode Base
    dest[2] = (source.base >> 0x00) & 0xFF;
    dest[3] = (source.base >> 0x08) & 0xFF;
    dest[4] = (source.base >> 0x10) & 0xFF;
    dest[7] = (source.base >> 0x18) & 0xFF;

    // Copy access byte
    dest[5] = source.access;
}

// Automatic Default Configuration
void gdt_auto(void)
{
    // NULL selector
    gdt_encode(&buffer [0x00],
        (struct GDT_Entry) {.base = 0, .limit = 0, .access = 0x00}
    );

    // Kernel Code selector
    gdt_encode(&buffer [0x08],
        (struct GDT_Entry) {.base = 0x00000000, .limit = 0xFFFFFFFF, .access = 0x9A}
    );

    // Kernel Data selector
    gdt_encode(&buffer [0x10],
        (struct GDT_Entry) {.base = 0x00000000, .limit = 0xFFFFFFFF, .access = 0x92}
    );

    // Load GDT
    gdt_load(&buffer [0x00], sizeof(buffer));
}
