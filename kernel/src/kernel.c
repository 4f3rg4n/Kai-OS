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
    vmm_init();
    paging_init(kernel_vmm->pt_root); 
    acpi_init();
    shell();
}
 