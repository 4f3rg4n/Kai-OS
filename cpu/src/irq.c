#include "../include/irq.h"

void remap_irqs(){
    //ICW1 - send init process command.
    out8(MASTER_PIC_COMMAND, ICW1 | ICW4);
    out8(SLAVE_PIC_COMMAND, ICW1 | ICW4);

    //ICW2 - set new offsets to the master & slave irq's.
    out8(MASTER_PIC_DATA, NEW_MASTER_OFFSET);
    out8(SLAVE_PIC_DATA, NEW_SLAVE_OFFSET);

    //ICW3 - connect master pic to slave pic using the irq2 of the master.
    out8(MASTER_PIC_DATA, MASTER_IRQ_CONNECT_SLAVE);
    out8(SLAVE_PIC_DATA, SLAVE_IRQ_CONNECT_IN_MASTER);

    //ICW4 - start 8086 mode in both pic's.
    out8(MASTER_PIC_DATA, ICW4);
    out8(SLAVE_PIC_DATA, ICW4);

    //OCW1 - enable using irq's from both pic's.
    out8(MASTER_PIC_DATA, UNMASKING_VALUE);
    out8(SLAVE_PIC_DATA, UNMASKING_VALUE);
}

void irq_init(){
    idt_set_new_gate(irq00_offset, (u32bit)irq00, 0x08, 0x8E);
    idt_set_new_gate(irq01_offset, (u32bit)irq01, 0x08, 0x8E);
    idt_set_new_gate(irq02_offset, (u32bit)irq02, 0x08, 0x8E);
    idt_set_new_gate(irq03_offset, (u32bit)irq03, 0x08, 0x8E);
    idt_set_new_gate(irq04_offset, (u32bit)irq04, 0x08, 0x8E);
    idt_set_new_gate(irq05_offset, (u32bit)irq05, 0x08, 0x8E);
    idt_set_new_gate(irq06_offset, (u32bit)irq06, 0x08, 0x8E);
    idt_set_new_gate(irq07_offset, (u32bit)irq07, 0x08, 0x8E);
    idt_set_new_gate(irq08_offset, (u32bit)irq08, 0x08, 0x8E);
    idt_set_new_gate(irq09_offset, (u32bit)irq09, 0x08, 0x8E);
    idt_set_new_gate(irq10_offset, (u32bit)irq10, 0x08, 0x8E);
    idt_set_new_gate(irq11_offset, (u32bit)irq11, 0x08, 0x8E);
    idt_set_new_gate(irq12_offset, (u32bit)irq12, 0x08, 0x8E);
    idt_set_new_gate(irq13_offset, (u32bit)irq13, 0x08, 0x8E);
    idt_set_new_gate(irq14_offset, (u32bit)irq14, 0x08, 0x8E);
    idt_set_new_gate(irq15_offset, (u32bit)irq15, 0x08, 0x8E);

    #ifdef DBG
    puts_c("IRQ init successfully\n", 0x0A);
    #endif
}