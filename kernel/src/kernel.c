#include "../include/kernel.h"

void kmain() {
    char name[10] = {0};

    cls(); //clean screen


    /*---------------*\
    | init os drivers | 
    \*---------------*/
    keyboard_init();
    idt_init();
    isr_init();
    timer_init();
    //asm volatile ("int $33");  // Trigger interrupt 1 manually

    shell();
}
