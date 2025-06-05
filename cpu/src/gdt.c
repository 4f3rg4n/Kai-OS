#include "../include/gdt.h"

/* Global GDT table and GDTR */
struct gdtr gdtr;
gdt_entry gdt[GDT_ENTRIES];

void gdt_init() {
    gdt_create_entry(0, 0, 0, 0, 0); // NULL segment (not used)
    gdt_create_entry(1, 0, MAX_ENTRY_LIMIT, GDT_ACCESS_KERNEL_CODE, SEG_GRANULARITY);  // Kernel CS
    gdt_create_entry(2, 0, MAX_ENTRY_LIMIT, GDT_ACCESS_KERNEL_DATA, SEG_GRANULARITY);  // Kernel DS
    gdt_create_entry(3, 0, MAX_ENTRY_LIMIT, GDT_ACCESS_USER_CODE, SEG_GRANULARITY);    // User   CS
    gdt_create_entry(4, 0, MAX_ENTRY_LIMIT, GDT_ACCESS_USER_DATA, SEG_GRANULARITY);    // User   DS

    
    //setup GDTR
    gdtr.limit = GDT_ENTRIES - 1;
    gdtr.base = (u32bit)&gdt;

    //load the new GDT
    gdt_load(&gdtr);
    //reload_segments((gdt_entry*)((u32bit)&gdt - (u32bit)&gdt[1])); 
    dbg_ok("GDT init succsessfully\n");
}

void gdt_load(struct gdtr* gdtr) {
    __asm__ __volatile__("lgdt (%0)" : : "r" (gdtr));
}

inline gdt_entry gdt_get_entry(u8bit index) {
    return gdt[index];
} 

inline void gdt_set_entry(u8bit index, gdt_entry entry) {
    gdt[index].limit_low   = entry.limit_low;
    gdt[index].base_low    = entry.base_low;
    gdt[index].base_middle = entry.base_middle;
    gdt[index].base_high   = entry.base_high;
    gdt[index].granularity = entry.granularity;
    gdt[index].access      = entry.access;
}

void gdt_create_entry(u8bit index, u32bit base, u32bit limit, u8bit access, u8bit granularity) {
    gdt[index].limit_low   = GET_LOW(limit);
    gdt[index].base_low    = GET_LOW(base);
    gdt[index].base_middle = GET_MID(base);
    gdt[index].base_high   = GET_HIG(base);
    gdt[index].granularity = granularity;
    gdt[index].access      = access;
}
