#ifndef PAGING_H
#define PAGING_H

#include "../../libc/include/types.h"

#define PAGE_SIZE 4096
#define PAGE_ENTRIES 1024

extern u32bit page_directory[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
extern u32bit page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));

void init_paging();
void page_directory_load(u32bit* page_directory);
void enable_paging();

#endif