#ifndef GDT_H
#define GDT_H

#include "../../libc/include/types.h"

typedef struct __attribute__((packed)) {
    u16bit limit_low;         // Limit bits 0-15
    u16bit base_low;          // Base bits 0-15
    u8bit  base_middle;       // Base bits 16-23
    u8bit  access;            // Access flags
    u8bit  granularity;       // Granularity flags
    u8bit  base_high;         // Base bits 24-31
} gdt_entry;

typedef struct __attribute__((packed)) {
    u16bit limit;       
    u32bit base;  
} gdtr;

void gdt_init();
void gdt_load(gdtr* gdtr);



#endif