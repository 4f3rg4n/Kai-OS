#include "../include/idt.h"

//idt
idt_entry idt[IDT_ENTRYS];

//idt pointer
idt_ptr idtr;

void idt_set_new_gate(u8bit entry, u32bit base, u16bit sel, u8bit flags) {
    idt[entry].base_low = (base & 0xFFFF);        //low 16 bits
    idt[entry].base_high = (base >> 16) & 0xFFFF; //high 16 bits
    idt[entry].sel = sel;                         
    idt[entry].all_zero = 0;                      
    idt[entry].flags = flags; 
}

void idt_init() {
    idtr.limit = (sizeof(idt_entry) * IDT_ENTRYS) - 1;
    idtr.base = (u32bit)&idt;
    idt_load();

    // log msg
    dbg_ok("IDT init successfully\n");
}

void idt_load() {
    __asm__ __volatile__("lidt (%0)" : : "r" (&idtr));
}
