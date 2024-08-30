#ifndef ISR_H
#define ISR_H

#include "idt.h"
#include "../../../libs/include/types.h"
#include "../../../libs/include/stdlib.h"

void isr_init();
void isr_handler(u16bit entry);

extern void isr0();  
extern void isr1();  
extern void isr2();
extern void isr3();  
extern void isr4();
extern void isr5();  
extern void isr6();
extern void isr7();  
extern void isr8();
extern void isr9();  
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

#endif