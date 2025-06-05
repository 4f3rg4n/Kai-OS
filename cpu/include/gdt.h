#ifndef GDT_H
#define GDT_H

#include "../../libc/include/types.h"

// Entryes data
#define GDT_ENTRIES 5
#define MAX_ENTRY_LIMIT 0xFFFFFFFF

/* Addrs helper macros */
#define GET_LOW(val) (val & 0xffff)
#define GET_MID(val) ((val >> 16) & 0xff)
#define GET_HIG(val) ((val >> 24) & 0xff)

    /*-------*\
    |* FLAGS *|
    \*-------*/

// Present flag
#define SEG_PRESENT      0x80    // Bit 7: Segment is present

// Descriptor Privilege Level (DPL) values
#define SEG_DPL_KERNEL   0x00    // Kernel level (Privilege Level 0)
#define SEG_DPL_USER     0x03    // User level (Privilege Level 3)

// Segment Type flags
#define SEG_TYPE_CODE    0x10    // Code Segment (Executable)
#define SEG_TYPE_DATA    0x00    // Data Segment (Non-Executable)

// Access flags
#define SEG_READWRITE    0x02    // Read/Write for data segments
#define SEG_EXECREAD     0x08    // Execute/Read for code segments

// Granularity flag
#define SEG_GRANULARITY  0x80    // 32-bit segment, 4KB granularity

// Macros for setting access byte
#define GDT_ACCESS_KERNEL_CODE  (SEG_PRESENT | SEG_DPL_KERNEL | SEG_TYPE_CODE | SEG_EXECREAD)
#define GDT_ACCESS_KERNEL_DATA  (SEG_PRESENT | SEG_DPL_KERNEL | SEG_TYPE_DATA | SEG_READWRITE)
#define GDT_ACCESS_USER_CODE    (SEG_PRESENT | SEG_DPL_USER   | SEG_TYPE_CODE | SEG_EXECREAD)
#define GDT_ACCESS_USER_DATA    (SEG_PRESENT | SEG_DPL_USER   | SEG_TYPE_DATA | SEG_READWRITE)

/* GDT entry structure */
typedef struct __attribute__((packed)) {
    u16bit limit_low;        
    u16bit base_low;         
    u8bit  base_middle;      
    u8bit  access;           
    u8bit  granularity;      
    u8bit  base_high;        
} gdt_entry;

/* GDTR register structure */
struct gdtr {
    u16bit limit;       
    u32bit base;  
}__attribute__((packed));

/* Global GDT table and GDTR */
extern struct gdtr gdtr;
extern gdt_entry gdt[GDT_ENTRIES];

extern reload_segments(gdt_entry* entry);

void gdt_init();
void gdt_load(struct gdtr* gdtr);
gdt_entry gdt_get_entry(u8bit index);
void gdt_set_entry(u8bit index, gdt_entry entry);
void gdt_create_entry(u8bit index, u32bit base, u32bit limit, u8bit access, u8bit granularity);

#endif
