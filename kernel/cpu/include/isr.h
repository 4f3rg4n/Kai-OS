#ifndef ISR_H
#define ISR_H

#include "idt.h"
#include "../../../libs/include/types.h"
#include "../../../libs/include/stdlib.h"

void isr_init();
void isr_handler(u16bit entry);

extern void isr0();  
extern void isr1();

#endif