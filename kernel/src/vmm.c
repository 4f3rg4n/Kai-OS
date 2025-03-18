/* Implementation of Virtual-Memory-Manager */

#include "../include/vmm.h"

vmm_obj* vmms = nullptr;
vmm_obj* kernel_vmm = nullptr;

void vmm_init() {
    kernel_vmm = vmm_create(KERNEL_LENGTH, VM_WRITEABLE, nullptr, KERNEL_RING);
    map_kernel(kernel_vmm);  
    dbg_ok("VMM init successfully\n");
}

void set_flags(vmm_obj* vm_object, u8bit is_writeable, u8bit is_exec, u8bit is_user) {
    u32bit flags = 0;
    flags |= is_writeable;
    flags |= is_exec << 1;
    flags |= is_user << 2;

    vm_object->flags = flags;
}

void* vmm_create(u32bit length, u32bit flags, void* arg, u8bit ring) {
    length = PAGE_ALIGN(length);
    vmm_obj* new_obj = (vmm_obj*)kmalloc(sizeof(vmm_obj), 0);
    new_obj->flags = flags;
    new_obj->length = length;
    vmms->pt_root = pmm_alloc_page();

    //set the virtual address according the privilages (ring)
    if(ring == KERNEL_RING)
        new_obj->base_addr = (void*)0x80000000;
    else if(ring == USER_RING)
        new_obj->base_addr = (void*)0x4f30000;

    new_obj->next = vmms;
    vmms = new_obj;
}

void map_memory(vmm_obj* vmm) {
    for(int i = 0; i < vmm->length / PAGE_SIZE; i++)
        map_addr(vmm->pt_root, vmm->base_addr, (u32bit)pmm_alloc_page(), vmm->flags);
}

void map_kernel(vmm_obj* vmm) {
    for (u32bit addr = 0; addr < vmm->length; addr += PAGE_SIZE)
        map_addr(vmm->pt_root, addr, addr, vmm->flags);  // Present + Writable
}
