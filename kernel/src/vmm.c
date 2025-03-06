/* Implementation of Virtual-Memory-Manager */

#include "../include/vmm.h"

vmm_obj* vmms = nullptr;

void vmm_init() {
    vmms = (vmm_obj*)kalloc(sizeof(vmm_obj));
    dbg_ok("VMM init successfully\n");
}

void set_flags(vmm_obj* vm_object, u8bit is_writeable, u8bit is_exec, u8bit is_user) {
    u32bit flags = 0;
    flags |= is_writeable;
    flags |= is_exec << 1;
    flags |= is_user << 2;

    vm_object->flags = flags;
}

void* vmm_create(u32bit length, u32bit flags, void* arg) {
    length = PAGE_ALIGN(length);
    vmm_obj* new_obj = pmm_alloc_page();
    new_obj->flags = flags;
    new_obj->length = length;
    
    //new_obj->base_addr = NULL; //need to be map into virt addr

    if(!vmms) {
        dbg_err("Internal Error: VMM is not defined!\n");
        return;
    }

    new_obj->next = vmms->next;
    vmms->next = new_obj;
}

void map_memory(void* vpt_root, void* phys, void* virt, u32bit flags) {

}
