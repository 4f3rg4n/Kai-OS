#include "../include/irq.h"

// global irq handlers
void* irq_handlers[IRQS] = {0};

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

    //OCW1 - disable all IRQs initially (0xFF masks everything).
    out8(MASTER_PIC_DATA, MASKING_VALUE);  // Disable all master PIC IRQs.
    out8(SLAVE_PIC_DATA, MASKING_VALUE);   // Disable all slave PIC IRQs.
}


/*
This function used to setup the irq handlers addresses inside the idt table,
and to prevent overwrite of the cpu interrupts by the pic irq's using remaping.
Output - Null.
*/
void irq_init(){
    remap_irqs();

    idt_set_new_gate(irq00_offset, (u32bit)irq00, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq01_offset, (u32bit)irq01, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq02_offset, (u32bit)irq02, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq03_offset, (u32bit)irq03, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq04_offset, (u32bit)irq04, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq05_offset, (u32bit)irq05, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq06_offset, (u32bit)irq06, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq07_offset, (u32bit)irq07, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq08_offset, (u32bit)irq08, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq09_offset, (u32bit)irq09, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq10_offset, (u32bit)irq10, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq11_offset, (u32bit)irq11, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq12_offset, (u32bit)irq12, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq13_offset, (u32bit)irq13, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq14_offset, (u32bit)irq14, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(irq15_offset, (u32bit)irq15, KERNEL_CS, INTERRUPT_GATE);

    // turn on interrupts
    asm volatile("sti");

    // log msg
    dbg_ok("IRQ init successfully\n");
}

u8bit get_master_IMR() {
    return in8(MASTER_PIC_DATA); // read the master PIC IMR
}

u8bit get_slave_IMR() {
    return in8(SLAVE_PIC_DATA); // read the slave PIC IMR
}

void set_master_IMR(u8bit imr) {
    out8(MASTER_PIC_DATA, imr);
}

void set_slave_IMR(u8bit imr) {
    out8(SLAVE_PIC_DATA, imr);
}

void enable_irq(u8bit offset) {
    u8bit imr = (offset < 8) ? get_master_IMR() : get_slave_IMR(); // get slave / master IMR by the given offset.
    imr &= ~(1 << offset);  // enable irq bit by set the bit to 1 by using 'not' & 'and' bitwise
    (offset < 8) ? set_master_IMR(imr) : set_slave_IMR(imr); // set IMR
}

void disable_irq(u8bit offset) {
    u8bit imr = (offset < 8) ? get_master_IMR() : get_slave_IMR(); // get slave / master IMR by the given offset.
    imr |= (1 << offset);  // disable irq bit by set the bit to 0 using 'or' bitwise
    (offset < 8) ? set_master_IMR(imr) : set_slave_IMR(imr); // set IMR
}

void irq_set_handler(u8bit offset, void* handler) {
    enable_irq(offset - 0x20);
    irq_handlers[offset - 0x20] = handler;
}

void irq_del_handler(u8bit offset) {
    disable_irq(offset - 0x20);
    irq_handlers[offset] = 0;
}

void irq_handler(u16bit entry) {
    void (*handler)(void);

    // get irq handler
    handler = irq_handlers[entry - 0x20];
    if (handler) { // check if the handler addr isnt empty
        handler(); // run handler
    }

    // sending End Of Interrupt (EOI) to the pic of the irq
    ((entry - 0x20) < 8) ? out8(MASTER_PIC_COMMAND, EOI) : out8(SLAVE_PIC_COMMAND, EOI);
}
