#include "../include/kheap.h"

heap_bin* heap_bins[BINS];
u32bit* heap_arena = HEAP_BASE;

void init_heap() {
    for(int idx = 1; idx < 8; idx++){
        heap_bins[fast_bin] = (heap_bin*)create_heap_obj(sizeof(heap_bin*)); 
        heap_bins[fast_bin]->max_size = idx
    }
}

void* create_heap_obj(u32bit obj_size) {
    void* addr = heap_arena;
    heap_arena += obj_size;
    return addr;
}

void* kalloc(u32bit size){
    void* addr = nullptr;

    if(size > PAGE_SIZE)
        return nullptr;

    if(curr_page == nullptr || size + page_ctr > PAGE_SIZE) {
        page_ctr = 0;
        curr_page = pmm_alloc_page() + sizeof(u32bit);
        update_ctr(curr_page, 0);
    }

    update_ctr(curr_page, get_ctr(curr_page) + 1);
    addr = page_ctr + size + curr_page;
    page_ctr += size;
    return addr;
}

void* kfree(void* addr) {
    if(get_ctr(addr) == 1) {
        curr_page = ((void*)PAGE_ALIGN_DOWN((u32bit)addr) == (curr_page - sizeof(u32bit)) ? nullptr : curr_page);
        pmm_free_page((void*)PAGE_ALIGN_DOWN((u32bit)addr));
    }
    else {
        update_ctr(addr, get_ctr(addr) - 1);
    }
}

