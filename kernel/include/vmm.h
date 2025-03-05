/* Implementation of Virtual-Memory-Manager */

#ifndef VMM_H
#define VMM_H

#include "pmm.h"
#include "paging.h"

#define PAGE_ALIGN(value) (value + (PAGE_SIZE - (value % PAGE_SIZE)))

typedef struct __attribute__((packed)) {
    void* base_addr;
    u32bit length;
    u32bit flags;
    u32bit* pt_root;
    struct vmm_obj* next;
} vmm_obj;

extern vmm_obj* vmms;

void vmm_init();
void set_flags(vmm_obj* vm_object, u8bit is_writeable, u8bit is_exec, u8bit is_user);
void* vmm_alloc(u32bit length, u32bit flags, void* arg);
void map_memory(void* vpt_root, void* phys, void* virt, u32bit flags);
#endif
