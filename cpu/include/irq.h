#ifndef IRQ_H
#define IRQ_H

#include "../../debug/debug.h"
#include "../../drivers/include/io.h"

#define MASTER_PIC_COMMAND 0x20 // master pic command sending port
#define SLAVE_PIC_COMMAND 0xA0 // slave pic command sending port

#define MASTER_PIC_DATA 0x21 // master pic recv data port
#define SLAVE_PIC_DATA 0xA1 // slave pic recv data port

#define NEW_MASTER_OFFSET 0x20 // after the CPU excptions interrupts
#define NEW_SLAVE_OFFSET 0x28 // after the master irq's

#define SLAVE_IRQ_CONNECT_IN_MASTER 0b00000010 // the irq2 in master using to connect with the slave pic.

/* 
* bit(4) = 1 - tell the pic that we start the initialization process.
*/
#define ICW1 0b00010000 // command for both master & slave pic's.

/*
bit(0) = 1 - this bit config the pic to work in 8086/88 mode.
*/
#define ICW4 0b00000001 // command for both master & slave pic's.

/* we set the third bit to tell the IMR (Interrupt Mask Register) 
that we want to connect the irq 2 to the slave pic */
#define MASTER_IRQ_CONNECT_SLAVE 0b00000100 

/* after the initialization process all the IMR bits are masking, 
this is security step to save us from call to wrong irq's. */
#define UNMASKING_VALUE 0 

enum irqs{
    //start of master irq's
    irq00_offset = NEW_MASTER_OFFSET,
    irq01_offset,
    irq02_offset,
    irq03_offset,
    irq04_offset,
    irq05_offset,
    irq06_offset,
    irq07_offset,
    //start of slave irq's
    irq08_offset = NEW_SLAVE_OFFSET,
    irq09_offset,
    irq10_offset,
    irq11_offset,
    irq12_offset,
    irq13_offset,
    irq14_offset,
    irq15_offset,
};

void remap_irqs();
void irq_init();
void irq_handler();

#endif