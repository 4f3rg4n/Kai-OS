/* Implementation of Virtual-Memory-Manager */

#include "../include/vmm.h"

vmm_obj* vmm;

void vmm_init() {
    vmm->vm_objects = (vmm_obj*)pmm_alloc_page();
    dbg_ok("VMM init successfully\n");
}

void set_flags(vm_obj* vm_object, u8bit is_writeable, u8bit is_exec, u8bit is_user) {
    u32bit flags = 0;
    flags |= is_writeable;
    flags |= is_exec << 1;
    flags |= is_user << 2;

    vm_object->flags = flags;
}

void* vmm_alloc(u32bit length, u32bit flags, void* arg) {

    length = ALIGN_LENGTH(length);
    vm_obj* new_obj = pmm_alloc_page();
    new_obj->flags = flags;
    new_obj->length = length;
    
    new_obj->base_addr = NULL; //need to be map into virt addr

    if(!vmm) {
        dbg_err("Internal Error: VMM is not defined!\n");
        return;
    }

    vm_obj* pvm_objects = vmm->vm_objects;
    
    while(pvm_objects->next)
        pvm_objects = pvm_objects->next;
    
    pvm_objects->next = new_obj;
}



