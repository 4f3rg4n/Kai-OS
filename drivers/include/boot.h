#ifndef BOOT_H
#define BOOT_H

#include "../../libc/include/memory.h"
#include "../../libc/include/types.h"

#define START_OF_BPB 0x7c02

typedef struct __attribute__((packed)) {
    char OEM_name[8];
    u16bit bytes_per_sectors;
    u8bit sectors_per_cluster;
    u16bit reserved_sectors;
    u8bit number_of_FATs;
    u16bit maximum_root_directory_entries;
    u16bit total_sectors;
    u8bit media_descriptor;
    u16bit sectors_per_FAT;
    u16bit sectors_per_track;
    u16bit number_of_heads;
    u32bit hidden_sectors;
    u32bit large_total_sectors;
} bios_parameter_block;

bios_parameter_block* get_bpb();

#endif