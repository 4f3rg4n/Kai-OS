#include "../include/kernel.h"

void kmain() {
    char name[10] = {0};
    
    cls(); //clean screen

    /*---------------*\
    | init os drivers | 
    \*---------------*/
    isr_init();
    irq_init();
    timer_init();
    keyboard_init();
    idt_init();

    shell();
}
