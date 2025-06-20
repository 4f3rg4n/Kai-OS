#include "../include/kheap.h"

heap_bin* heap_bins[BINS];
u32bit* heap_arena = KHEAP_BASE;

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
    
    dbg_ok("Heap init successfully\n");
}

void* create_heap_obj(u32bit obj_size) {
    if(heap_arena + obj_size > KHEAP_BASE + KHEAP_SIZE)
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

heap_bin* search_bin_by_size(u32bit size) {
    heap_bin* bin = nullptr;
    size = ALIGN_CHUNK_SIZE(size);

    if(size <= fbsize * fbins_num)
        bin = heap_bins[fast_bin];
    else if(size <= sbsize * sbins_num)
        bin = heap_bins[small_bin];
    else if(size <= lbsize * lbins_num)
        bin = heap_bins[large_bin];
    else
        return heap_bins[unsorted_bin];

    while(bin->max_size < size || bin != nullptr)
        bin = bin->next;

    return bin;
}

heap_chunk* search_free_chunk(heap_bin* bin, u32bit size) {
    //bin is empty
    if (bin->chunks == nullptr) return nullptr;

    //is unsorted?
    if(heap_bins[unsorted_bin] == bin)
        return unsorted_bin_search(size);

    heap_chunk* chunk = bin->chunks;
    do {
        //size check
        if(chunk->size_n_flags & MAX_CHUNK_SIZE == size) {
            UNLINK(chunk);
            return chunk;
        }
        chunk = chunk->fd;
    } while(chunk && chunk != bin->chunks);

    return nullptr;
}

heap_chunk* unsorted_bin_search(u32bit size) {
    heap_bin* bin = heap_bins[unsorted_bin];
    heap_chunk* chunk = bin->chunks->bk;

    do {
        //unlink chunk from unsorted bin
        PARTIAL_UNLINK(chunk, bin->chunks);

        //size check
        if((chunk->size_n_flags & MAX_CHUNK_SIZE) == size)
            return chunk;

        insert_chunk_into_bin(chunk, search_bin_by_size(chunk->size_n_flags));
        chunk = chunk->bk;
    } while(chunk != bin->chunks->bk);

    return nullptr;
}

void insert_chunk_into_bin(heap_chunk* chunk, heap_bin* bin) {
    if(bin->chunks) {
        bin->chunks->prev_size = chunk->size_n_flags;
        chunk->fd = bin->chunks;
        chunk->bk = bin->chunks->bk;
        bin->chunks->bk = chunk;
    }

    bin->chunks = chunk;
}

void* kfree(void* addr) {
    heap_chunk* chunk = (heap_chunk*)(addr - sizeof(heap_chunk));
    chunk->size_n_flags &= ~CHUNK_ALLOCATED;
    insert_chunk_into_bin(chunk, search_bin_by_size(chunk->size_n_flags));

    return nullptr;
}

void* kmalloc(u32bit size, u32bit flags){
    size = ALIGN_CHUNK_SIZE(size);
    heap_bin* bin = search_bin_by_size(size);
    heap_chunk* chunk = search_free_chunk(bin, size);

    if(chunk == nullptr) {
        chunk = (heap_chunk*)create_heap_obj(size + sizeof(heap_chunk));
    }

    chunk->fd = nullptr;
    chunk->bk = nullptr;
    chunk->prev_size = 0;

    chunk->size_n_flags = size | CHUNK_ALLOCATED;
    return ((void*)chunk + sizeof(heap_chunk));
}

void* kcalloc(u32bit size) {
    void* ptr = kmalloc(size, 0);
    if(!ptr) return nullptr;
    memset(ptr, 0, size); //erase all the chunk bytes

    return ptr;
}

void* realloc(void* ptr, u32bit size) {
    if(!ptr) return kmalloc(size, 0);
    if(!size) { kfree(ptr); return nullptr;}

    void* new_ptr = kmalloc(size, 0);
    if(!new_ptr) return nullptr;
    memcpy(new_ptr, ptr, size);
    kfree(ptr);
    kmalloc(size, 0);

    return new_ptr;
}

