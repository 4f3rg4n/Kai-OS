#ifndef PAGING_H
#define PAGING_H

#include "../../libc/include/types.h"
#include "../../cpu/include/isr.h"

#define PAGE_SIZE 4096
#define PAGE_ENTRIES 1024
#define PDE_NUM 3
#define PTE_NUM 1024

extern u32bit* page_directory; 

void paging_init();
void page_directory_load(u32bit* page_directory);

void enable_paging();
void page_fault_handler();

int create_page_entry(int, char, char, char, char, char, char, char, char);

#endif