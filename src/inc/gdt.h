#include <stdint.h>
#include <stdbool.h>

#ifndef GDT_H
#define GDT_H

// Buffer for GDT
static uint8_t buffer [0x18];

// GDT Structure Element
struct GDT_Entry
{
    uint32_t base;
    uint32_t limit;
    uint8_t access;
};

// GDT Functions
void gdt_encode(uint8_t*, struct GDT_Entry);
void gdt_load(uint8_t*, uint16_t);

// GDT Auto-config
void gdt_auto(void);

#endif
