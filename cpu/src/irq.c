#include "../include/irq.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

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