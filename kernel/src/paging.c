#include "../include/paging.h"

u32bit page_directory[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
u32bit page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));

void init_paging() {
    //map phisical memory to virtual memory (4KB pages equals to 4MB of memory)
    for (u32bit i = 0; i < PAGE_ENTRIES; i++) {
        page_table[i] = (i * PAGE_SIZE) | 3; // FLAGS: Present, Read/Write
    }

    //the first page directory entry point to the page table
    page_directory[0] = ((u32bit)page_table) | 3; // FLAGS: Present, Read/Write

    //clear other entries
    for (u32bit i = 1; i < PAGE_ENTRIES; i++) {
        page_directory[i] = 0; //not present
    }

    page_directory_load(page_directory);
    enable_paging();
    idt_set_new_gate(14, (u32bit)page_fault_handler, KERNEL_CS, INTERRUPT_GATE);

    // log msg
    dbg_ok("Paging init successfully\n");
}

void page_directory_load(u32bit* page_directory){
    asm volatile("mov %0, %%cr3" : : "r"(page_directory));
}

void enable_paging(){
    u32bit cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0)); 
    cr0 |= 0x80000000; 
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

void page_fault_handler() {
    int faulting_address;
    asm volatile("mov %%cr2, %0" : "=r"(faulting_address));
    puts("Page fault in addr ");
    puti(faulting_address & 0xffff);
    puts("\n");
    while (1==1){}
    
}