#include "../include/idt.h"

void set_new_idt_gate(u8bit num, u32bit base, u16bit sel, u8bit flags) {
    idt[num].base_low = (base & 0xFFFF);        //low 16 bits
    idt[num].base_high = (base >> 16) & 0xFFFF; //high 16 bits
    idt[num].sel = sel;                         
    idt[num].all_zero = 0;                      
    idt[num].flags = flags; 
}

void idt_init() {
    idtr.limit = (sizeof(idt_entry) * IDT_ENTRYS) - 1;
    idtr.base = (u32bit)&idt;
    idt_load();
}

void idt_load() {
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idtr));
}
