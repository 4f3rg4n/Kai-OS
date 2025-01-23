#include "../include/paging.h"
#include "../include/pmm.h"

u32bit* page_directory; 

void paging_init() {
    unsigned int curr_page_frame = 0;
    page_directory = pmm_alloc_page();

    for (int currPDE = 0; currPDE < PDE_NUM; ++currPDE) {
        unsigned *pageTable = pmm_alloc_page();

        for (int currPTE = 0; currPTE < PTE_NUM; ++currPTE, ++curr_page_frame) 
            pageTable[currPTE] = create_page_entry(curr_page_frame * 4096, 1, 0, 0, 1, 1, 0, 0, 0);

        page_directory[currPDE] = create_page_entry(pageTable, 1, 0, 0, 1, 1, 0, 0, 0); 
    }

    page_directory_load(page_directory);
    idt_set_new_gate(14, (u32bit)page_fault_handler, KERNEL_CS, INTERRUPT_GATE);
    enable_paging();

    // Log success
    dbg_ok("Paging initialized successfully\n");
}


int create_page_entry(int base_address, char is_present, char is_writable, char privilege_level, char is_cache_enabled, char write_through_cahce, char is_accessed, char page_size, char is_dirty) { 
    int entry = 0;

    entry |= is_present;
    entry |= is_writable << 1;
    entry |= privilege_level << 2;
    entry |= write_through_cahce << 3;
    entry |= is_cache_enabled << 4;
    entry |= is_accessed << 5;
    entry |= is_dirty << 6;
    entry |= page_size << 7;

    return base_address | entry;

}

void page_directory_load(u32bit* page_directory) {
    u32bit cr3;
    asm volatile("mov %0, %%cr3" : : "r"(page_directory)); // Load page directory base into CR3
}

void enable_paging() {
    u32bit cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0)); 
    cr0 |= 0x80000000; // set the paging (PG) bit in CR0
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

void page_fault_handler() {
    u32bit addr;
    asm volatile("mov %%cr2, %0" : "=r"(addr)); // get the faulting address from CR2

    printf("Page fault at address: 0x%x\n",addr);
    while (1) {} //hlt
}
