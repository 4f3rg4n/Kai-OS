#include "../include/paging.h"
#include "../include/pmm.h"

u32bit* page_directory; 
u32bit* page_table;    

void init_paging() {
    page_directory = (u32bit*)pmm_alloc_page();
    if(page_directory == PAGE_NOT_FOUND)
        return;
    memset(page_directory, 0, PAGE_SIZE);

    page_table = (u32bit*)pmm_alloc_page();
    if(page_table == PAGE_NOT_FOUND)
        return;
    memset(page_table, 0, PAGE_SIZE);

    for (u32bit i = 0; i < PAGE_ENTRIES; i++) {
        u32bit frame = pmm_alloc_page();
        if(frame == PAGE_NOT_FOUND)
            break;
        page_table[i] = frame | 3; // FLAGS: Present, Read/Write
    }
    page_directory[0] = ((u32bit)page_table) | 3; // FLAGS: Present, Read/Write

    for (u32bit i = 1; i < PAGE_ENTRIES; i++) {
        page_directory[i] = 0; // * Not present *
    }

    page_directory_load(page_directory);

    enable_paging();
    return;

    // steup page fault handler
    idt_set_new_gate(14, (u32bit)page_fault_handler, KERNEL_CS, INTERRUPT_GATE);

    // Log success
    dbg_ok("Paging initialized successfully\n");
}

void page_directory_load(u32bit* page_directory) {
    asm volatile("mov %0, %%cr3" : : "r"(page_directory)); // Load page directory base into CR3
}

void enable_paging() {
    u32bit cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0)); 
    cr0 |= 0x80000000; // set the paging (PG) bit in CR0
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

void page_fault_handler() {
    u32bit faulting_address;
    asm volatile("mov %%cr2, %0" : "=r"(faulting_address)); // get the faulting address from CR2

    puts("Page fault at address: ");
    puti(faulting_address);
    puts("\n");

    while (1) {} //hlt
}
