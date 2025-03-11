#ifndef PAGING_H
#define PAGING_H

#include "../../libc/include/types.h"
#include "../../cpu/include/isr.h"
#include "kerrors.h"

#define PAGE_SIZE 4096
#define PDE_NUM 1024
#define PTE_NUM 1024

#define GET_BASE_ADDR(addr) (addr & 0xFFFFF000)
#define UNAMP_ADDR(addr) (addr ^= addr)

extern u32bit* page_directory; 

void paging_init();
void page_directory_load(u32bit* page_directory);

void enable_paging();
void page_fault_handler();
void map_addr(void* pt_root, u32bit base_addr, u32bit addr, u32bit flags);
void unmap_addr(void* pt_root, u32bit base_addr);

u32bit create_page_entry(u32bit base_address, u8bit is_present, u8bit is_writable, u8bit privilege_level, u8bit is_cache_enabled, u8bit write_through_cahce, u8bit is_accessed, u8bit page_size, u8bit is_dirty);

#endif