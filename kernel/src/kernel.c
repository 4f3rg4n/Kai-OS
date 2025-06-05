#include "../include/kernel.h"

void kmain() {  
    cls(); //clean screen

    /*---------------*\
    | init os drivers |
    \*---------------*/
    //gdt_init();
    isr_init();
    irq_init();
    timer_init();
    keyboard_init();
    idt_init();
    pmm_init(MEMORY_LIMIT);
    init_heap();
    //vmm_init();
    //paging_init(kernel_vmm->pt_root); 
    acpi_init();

    /*-------------*\
    |  start shell  |
    \*-------------*/
    shell();
}
 