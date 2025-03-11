/* Implementation of Virtual-Memory-Manager */

#ifndef VMM_H
#define VMM_H

#include "pmm.h"
#include "paging.h"
#include "kheap.h"

#define PAGE_ALIGN(value) (value + (PAGE_SIZE - (value % PAGE_SIZE)))
#define KERNEL_LENGTH 0x400000

//rings privilages
#define KERNEL_RING 0
#define USER_RING 3

//flags
#define VM_WRITEABLE 1
#define VM_EXEC 2
#define VM_USER 4

typedef struct __attribute__((packed)) {
    void* base_addr;
    u32bit length;
    u32bit flags;
    u32bit* pt_root;
    struct vmm_obj* next;
} vmm_obj;

extern vmm_obj* vmms;
extern vmm_obj* kernel_vmm;

void vmm_init();
void set_flags(vmm_obj* vm_object, u8bit is_writeable, u8bit is_exec, u8bit is_user);
void* vmm_create(u32bit length, u32bit flags, void* arg, u8bit ring);
void map_memory(vmm_obj* vmm);
void map_kernel(vmm_obj* vmm);
#endif
