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
    pmm_init(MEMORY_LIMIT);
    paging_init();
    //vmm_init();
    shell();
}
 