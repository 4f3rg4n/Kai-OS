#ifndef KHEAP_H
#define KHEAP_H

#include "../../libc/include/stdlib.h"
#include "pmm.h"
#include "kerrors.h"

#define PAGE_SIZE 4096
#define PAGE_ALIGN_DOWN(value) (value - (value % PAGE_SIZE))

#define CHUNK_ALLOCATED  0x1  //allocated bit
#define CHUNK_MMAP       0x2  //nmap bit (for large allocations)
#define CHUNK_PREV_FREE  0x4  //previous chunk is free

#define HEAP_BASE 0x1000000
#define HEAP_SIZE 0x1000000

#define BINS 4

enum bins {
    fast_bin,
    small_bin,
    large_bin,
    unsorted_bin
};

enum min_bin_size{
    fbsize = 16,
    sbsize = 64,
    lbsize = 512,
    ubsize = 1024
};

enum num_of_bins{
    fbins_num = 7,
    sbins_num = 4,
    lbins_num = 7,
    ubins_num = 1
};

typedef struct __attribute__((packed)) {
    u32bit prev_size;
    u32bit size_n_flags;
    struct heap_chunk* fd;
    struct heap_chunk* bk;
} heap_chunk;

typedef struct __attribute__((packed)) {
    heap_chunk* top_chunk;
    heap_chunk* last_chunk;
    heap_chunk* first_chunk;
} heap;

typedef struct __attribute__((packed)) {
    heap_chunk* chunks;
    u32bit max_size;
    heap_bin* next;
} heap_bin;

extern heap_bin* heap_bins[BINS];
extern u32bit* heap_arena;

void init_heap();
void* create_heap_obj(u32bit obj_size);
heap_bin* create_bin(u32bit bin_size, heap_chunk* chunks);
heap_bin* get_bin(u32bit size);
void* kmalloc(u32bit size, u32bit flags);
void* kfree(void* addr);
#endif