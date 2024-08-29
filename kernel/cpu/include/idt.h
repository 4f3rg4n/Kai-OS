#ifndef IDT_H
#define IDT_H

#include "../../libs/include/types.h"

#define IDT_ENTRYS 256

typedef struct idt_entry {
    u16bit base_low;    
    u16bit sel;         
    u8bit  all_zero;     
    u8bit  flags;       
    u16bit base_high;   
} idt_entry __attribute__((packed)) /*no padding*/; 

typedef struct idt_ptr {
    u16bit limit;       
    u32bit base;          
} idt_ptr __attribute__((packed)) /*no padding*/;

//idt
idt_entry idt[IDT_ENTRYS];

//idt pointer
idt_ptr idtr;

//idt helper functions
void set_new_idt_gate(u8bit num, u32bit base, u16bit sel, u8bit flags);
void idt_init();
void idt_load();

#endif