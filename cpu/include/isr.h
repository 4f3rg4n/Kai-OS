#ifndef ISR_H
#define ISR_H

#include "idt.h"
#include "../../libc/include/types.h"
#include "../../libc/include/stdlib.h"
#include "../../libc/include/strings.h"
#include "../../debug/debug.h"

void isr_init();
void isr_handler(u16bit entry);

extern void isr00();  
extern void isr01();  
extern void isr02();
extern void isr03();  
extern void isr04();
extern void isr05();  
extern void isr06();
extern void isr07();  
extern void isr08();
extern void isr09();  
extern void isr10();
extern void isr11();  
extern void isr12();
extern void isr13();  
extern void isr14();
extern void isr15();  
extern void isr16();
extern void isr17();  
extern void isr18();
extern void isr19();  
extern void isr20();
extern void isr21();  
extern void isr22();
extern void isr23();
extern void isr24();  
extern void isr25();
extern void isr26();  
extern void isr27();
extern void isr28();  
extern void isr29();
extern void isr30();  
extern void isr31();

#endif