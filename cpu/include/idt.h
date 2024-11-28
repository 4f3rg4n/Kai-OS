#ifndef IDT_H
#define IDT_H

#include "../../libc/include/types.h"
#include "../../libc/include/strings.h"

#define IDT_ENTRYS 256

typedef struct __attribute__((packed)) {
    u16bit base_low;    
    u16bit sel;         
    u8bit  all_zero;     
    u8bit  flags;       
    u16bit base_high;   
} idt_entry /*no padding*/; 

typedef struct __attribute__((packed)) {
    u16bit limit;       
    u32bit base;          
} idt_ptr /*no padding*/;

//idt
extern idt_entry idt[IDT_ENTRYS];

//idt pointer
extern idt_ptr idtr;

//idt helper functions
void idt_set_new_gate(u8bit entry, u32bit base, u16bit sel, u8bit flags);
void idt_init();
void idt_load();

#endif