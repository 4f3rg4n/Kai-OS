#include "../include/kheap.h"

void* curr_page = nullptr;
u32bit page_ctr = 0;

void* kalloc(u32bit size){
    void* addr = nullptr;

    if(size > PAGE_SIZE)
        return nullptr;

    if(size + page_ctr > PAGE_SIZE) {
        curr_page = pmm_alloc_page() + sizeof(u32bit);
        update_ctr(curr_page, 0);
    }

    update_ctr(curr_page, get_ctr(curr_page) + 1);
    addr = page_ctr + size + curr_page;
    page_ctr += size;
    return addr;
}

void* kfree(void* addr) {
    if(!get_ctr(addr))
        pmm_free_page((void*)PAGE_ALIGN_DOWN((u32bit)addr));
    else    
        update_ctr(addr, get_ctr(addr) - 1);
}

inline void update_ctr(void* page, u32bit ctr) {
    *(u32bit*)(PAGE_ALIGN_DOWN((u32bit)page)) = ctr;
}

inline u32bit get_ctr(void* page) {
    return *(u32bit*)(PAGE_ALIGN_DOWN((u32bit)page));
}