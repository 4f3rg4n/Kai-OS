#include "../include/kernel.h"

void kmain() {    
    cls(); //clean screen

    /*---------------*\
    | init os drivers |
    \*---------------*/
    isr_init();
    irq_init();
    timer_init();
    keyboard_init();
    idt_init();
    init_paging();
    u32bit *ptr = (u32bit *)0xDEADBEEF; // Use an invalid address (non-present page)
    *ptr = 0; // This will trigger a page fault


    shell();
}
