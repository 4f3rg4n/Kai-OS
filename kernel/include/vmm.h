/* Implementation of Virtual-Memory-Manager */

#ifndef VMM_H
#define VMM_H

#include "pmm.h"
#include "paging.h"

#define ALIGN_LENGTH(length) (length + (PAGE_SIZE - (length % PAGE_SIZE)))

typedef struct __attribute__((packed)) {
    u32bit* base_addr;
    u32bit length;
    u32bit flags;
    u32bit* pt_root;
    struct vm_obj* next;
} vm_obj;

typedef struct __attribute__((packed)) {
    vm_obj* vm_objects;
} vmm_obj;

extern vmm_obj* vmm;

void vmm_init();
void set_flags(vm_obj* vm_object, u8bit is_writeable, u8bit is_exec, u8bit is_user);
void* vmm_alloc(u32bit length, u32bit flags, void* arg);

#endif
