#include "../include/paging.h"
#include "../include/pmm.h"

u32bit* page_directory; 

void paging_init() {
    page_directory = pmm_alloc_page();

    for (u32bit addr = 0x0; addr < 0x400000; addr += PAGE_SIZE) {
        map_addr(page_directory, addr, addr, 0b11);  // Present + Writable
    }

    for (u32bit addr = 0x80000000; addr < 0x80800000; addr += PAGE_SIZE) {
        map_addr(page_directory, addr, addr, 0b11);  // Kernel memory mapping
    }

    page_directory_load(page_directory);
    enable_paging();
    idt_set_new_gate(14, (u32bit)page_fault_handler, KERNEL_CS, INTERRUPT_GATE);

    // Log success
    dbg_ok("Paging initialized successfully\n");
}


u32bit create_page_entry(u32bit base_address, u8bit is_present, u8bit is_writable, u8bit privilege_level, u8bit is_cache_enabled, u8bit write_through_cahce, u8bit is_accessed, u8bit page_size, u8bit is_dirty) { 
    u32bit entry = 0;

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

void map_addr(void* pt_root, u32bit base_addr, u32bit addr, u32bit flags) {
    u32bit* page_directory = (u32bit*)pt_root;

    // Extract indexes from base virtual address
    u32bit dir_idx = ((u32bit)base_addr >> 22) & 0x3FF;  // PDE index
    u32bit tbl_idx = ((u32bit)base_addr >> 12) & 0x3FF;  // PTE index

    // Check if page table exists
    if (!(page_directory[dir_idx] & 1)) { 
        // Allocate new page table if not present
        page_directory[dir_idx] = (u32bit)pmm_alloc_page() | 0b11; // Present + Writable
    }

    // Get the page table base
    u32bit* page_table = (u32bit*)(page_directory[dir_idx] & 0xFFFFF000);

    // Set the PTE to point to the physical address
    page_table[tbl_idx] = ((u32bit)addr & 0xFFFFF000) | flags;
}

void unmap_addr(void* pt_root, u32bit addr) {

}