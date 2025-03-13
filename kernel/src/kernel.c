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
    init_heap();
    char* str = (char*)kmalloc(4000, 0);
    putx(str);
    kfree(str);
    char* irl = (char*)kmalloc(50000, 0);
    putx(irl);
    //gets(irl);
    //puts(irl);
    //puts(str);
    //vmm_init();
    //paging_init(kernel_vmm->pt_root); 
    //acpi_init();
    //printf("%s", get_bpb()->OEM_name);
    //printf("%s", (char*) 0x7C05);  // Should also print the OEM string
    //shell();
}
 