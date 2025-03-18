/* Implementation of Physical-Memory-Manager */
#ifndef PMM_H
#define PMM_H

#include "../../libc/include/memory.h"
#include "../../libc/include/types.h"

#define PAGE_SIZE 4096           
#define BITMAP_SIZE 1024 << 5 // manage 128MB of memory
#define MEMORY_LIMIT ((BITMAP_SIZE) * PAGE_SIZE)
#define PAGE_NOT_FOUND 0

extern u8bit memory_bitmap[BITMAP_SIZE / 8];  
extern u32bit total_pages;                    

#define GET_BITMAP_INDEX(addr) ((addr) / PAGE_SIZE) // this macro return general bitmap index by given addr
#define GET_BITMAP_BYTE(index) ((index) / 8) // this macro return the bitmap byte index by given index
#define GET_BITMAP_BIT(index)  ((index) % 8) // this macro return the bit number inside the given byte index

void set_bit(u32bit index);
void clear_bit(u32bit index);
u8bit test_bit(u32bit index);
void* pmm_alloc_page();
void pmm_free_page(void* page);
void cls_bitmap(u32bit size);
void pmm_init(u32bit memory_size);

#endif