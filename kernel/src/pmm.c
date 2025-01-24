/* Implementation of Physical-Memory-Manager */

#include "../include/pmm.h"

u8bit memory_bitmap[BITMAP_SIZE / 8] = {0};  
u32bit total_pages;                    

void set_bit(u32bit index) {
    memory_bitmap[GET_BITMAP_BYTE(index)] |= (1 << GET_BITMAP_BIT(index));
}

void clear_bit(u32bit index) {
    memory_bitmap[GET_BITMAP_BYTE(index)] &= ~(1 << GET_BITMAP_BIT(index));
}

u8bit test_bit(u32bit index) { 
    return memory_bitmap[GET_BITMAP_BYTE(index)] & (1 << GET_BITMAP_BIT(index));
}

void* pmm_alloc_page() {
    for (u32bit i = 0; i < total_pages; i++) {
        if (!test_bit(i)) { 
            set_bit(i);   
            return (void*)((i * PAGE_SIZE)); 
        }
    }

    dbg_err("PMM Error: Free page not found.\n");
    return PAGE_NOT_FOUND; 
}

void pmm_free_page(void* page) {
    u32bit index = GET_BITMAP_INDEX((u32bit)page);
    if (index >= total_pages) {
        dbg_err("PMM Error: Free invalid page.\n");
        return;
    }

    clear_bit(index); 
}

void cls_bitmap(u32bit size) {
    memset(memory_bitmap, 0, size); 
}

void pmm_init(u32bit memory_size) {
    // memory size must be less then memory limit
    total_pages = (memory_size > MEMORY_LIMIT) ? (MEMORY_LIMIT / PAGE_SIZE) : (memory_size / PAGE_SIZE);
    cls_bitmap(sizeof(memory_bitmap));

    //kernel memory - 1MB
    for (u32bit i = 0; i < 256; i++)
        set_bit(i);

    dbg_ok("PMM init successfully\n");
}
