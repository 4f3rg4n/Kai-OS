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
    pmm_init(-1);
    paging_init();
    //vmm_init();
    shell();
}
