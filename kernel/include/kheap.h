#ifndef KHEAP_H
#define KHEAP_H

#include "../../libc/include/stdlib.h"
#include "pmm.h"

#define PAGE_SIZE 4096
#define PAGE_ALIGN_DOWN(value) (value - (value % PAGE_SIZE))

extern void* curr_page;
extern u32bit page_ctr;

void* kalloc(u32bit size);
void* kfree(void* addr);
inline void update_ctr(void* page, u32bit ctr);
inline u32bit get_ctr(void* page);
#endif