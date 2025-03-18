#ifndef KHEAP_H
#define KHEAP_H

#include "../../libc/include/stdlib.h"
#include "../../libc/include/memory.h"
#include "pmm.h"
#include "kerrors.h"

#define PAGE_SIZE 4096
#define PAGE_ALIGN_DOWN(value) (value - (value % PAGE_SIZE))

/* Flags */
#define CHUNK_ALLOCATED  0x1  //allocated bit
#define CHUNK_MMAP       0x2  //nmap bit (for large allocations)
#define CHUNK_PREV_FREE  0x4  //previous chunk is free

#define KHEAP_BASE 0x1000000
#define KHEAP_SIZE 0x1000000
#define MIN_CHUNK_SIZE 0x10
#define BINS 4

#define ALIGN_CHUNK_SIZE(size) (size + (MIN_CHUNK_SIZE - (size % MIN_CHUNK_SIZE)))

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
    ubsize = 4096
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
    heap_chunk* chunks;
    u32bit max_size;
    struct heap_bin* next;
} heap_bin;

typedef struct __attribute__((packed)) {
    heap_bin* bins[BINS];
    u32bit* start;
    u32bit* arena;
    u32bit size;
} heap_obj;

extern heap_bin* heap_bins[BINS];
extern u32bit* heap_arena;

void init_heap();
void* create_heap_obj(u32bit obj_size);
heap_bin* create_bin(u32bit bin_size, heap_chunk* chunks);
heap_bin* find_bin_by_size(u32bit size);
heap_chunk* find_chunk_in_bin(heap_bin* bin, u32bit size);
void insert_chunk_into_bin(heap_chunk* chunk, heap_bin* bin);
void* kmalloc(u32bit size, u32bit flags);
void* kcalloc(u32bit size, u32bit flags);
void* realloc(void* ptr, u32bit size);
void* kfree(void* addr);
#endif