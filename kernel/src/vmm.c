/* Implementation of Virtual-Memory-Manager */

#include "../include/vmm.h"

vmm_obj* vmms = nullptr;
vmm_obj* kernel_vmm = nullptr;

void vmm_init() {
    kernel_vmm = vmm_create(0x7fffffff, WRITEABLE, nullptr, KERNEL_RING);

 // Set up identity mapping for the kernel (or higher half kernel)
    for (u32bit addr = 0x0; addr < 0x1000000; addr += PAGE_SIZE) {
        // Map the physical address to the same virtual address (identity mapping)
        map_memory(vmms->pt_root, (void*)addr, (void*)(0x80000000 + addr), 0x3);  // 0x3 = Readable and Writable
    }

    // Enable paging with the page directory
    paging_init();  // This will load the page directory and enable paging.

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
    vmm_obj* new_obj = (vmm_obj*)kalloc(sizeof(vmm_obj));
    new_obj->flags = flags;
    new_obj->length = length;
    vmms->pt_root = pmm_alloc_page();

    //set the virtual address according the privilages (ring)
    if(ring == KERNEL_RING)
        new_obj->base_addr = (void*)0x80000000;
    else if(ring == USER_RING)
        new_obj->base_addr = (void*)0x4f300000;

    new_obj->next = vmms;
    vmms = new_obj;
}

void map_memory(void* pt_root, void* phys, void* virt, u32bit flags) {
    u32bit* page_table = (u32bit*)pt_root;
    u32bit page_idx = (u32bit)virt / PAGE_SIZE;
    page_table[page_idx] = (u32bit)phys | flags; //set the virt idx to point to the physical addr
}
