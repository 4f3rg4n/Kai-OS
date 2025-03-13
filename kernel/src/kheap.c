#include "../include/kheap.h"

heap_bin* heap_bins[BINS];
u32bit* heap_arena = HEAP_BASE;

void init_heap() {
    heap_bin* bin = nullptr;

    // Create fast bins
    bin = create_bin(fbsize, nullptr);
    heap_bins[fast_bin] = bin;
    for(int idx = 1; idx != fbins_num; idx++) {
        bin->next = create_bin((idx+1) * fbsize, nullptr);
        bin = bin->next;
    }

    // Create small bins
    bin = create_bin(sbsize, nullptr);
    heap_bins[small_bin] = bin;
    for(int idx = 1; idx != sbins_num; idx++) {
        bin->next = create_bin((idx+1) * sbsize, nullptr);
        bin = bin->next;
    }

    // Create large bins
    bin = create_bin(lbsize, nullptr);
    heap_bins[large_bin] = bin;
    for(int idx = 1; idx != lbins_num; idx++) {
        bin->next = create_bin((idx+1) * lbsize, nullptr);
        bin = bin->next;
    }

    // Create unsorted bin
    heap_bins[unsorted_bin] = create_bin(ubsize, nullptr);
}

void* create_heap_obj(u32bit obj_size) {
    if(heap_arena + obj_size > HEAP_BASE + HEAP_SIZE)
        panic("Heap out of memory!");
    void* addr = heap_arena;
    heap_arena += obj_size;
    return addr;
}

heap_bin* create_bin(u32bit bin_size, heap_chunk* chunks) {
    heap_bin* bin = (heap_bin*)create_heap_obj(sizeof(heap_bin*));
    bin->max_size = bin_size;
    bin->chunks = chunks;   
    bin->next = nullptr;
    return bin;
}

heap_bin* get_bin(u32bit size) {
    if(size <= fbsize * fbins_num)
        return heap_bins[fast_bin];
    else if(size <= sbsize * sbins_num)
        return heap_bins[small_bin];
    else if(size <= lbsize * lbins_num)
        return heap_bins[large_bin];
    else
        return heap_bins[unsorted_bin];
}

void* kmalloc(u32bit size, u32bit flags){
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

