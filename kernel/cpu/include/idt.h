#ifndef IDT_H
#define IDT_H

#include "../../libs/include/types.h"

struct idt_entry {
    u16bit base_low;    
    u16bit sel;         
    u8bit  zero;     
    u8bit  flags;       
    u16bit base_high;   
} __attribute__((packed)) /*no padding*/; 

struct idt_ptr {
    u16bit limit;       
    u32bit base;          
} __attribute__((packed)) /*no padding*/;

//idt
struct idt_entry idt[256];

//idt pointer
struct idt_ptr idtp;

//idt helper functions
void set_new_gate(u8bit num, u32bit base, u16bit sel, u8bit flags);
void idt_init();
void idt_load();

#endif