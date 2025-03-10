#include "../../libc/include/types.h"


#define RSDP_SEARCH_START 0x000E0000
#define RSDP_SEARCH_END   0x000FFFFF

typedef struct {
    char signature[8];  
    u8bit checksum;
    char oem_id[6];
    u8bit revision;
    u32bit rsdt_address;
} __attribute__((packed)) RSDPDescriptor;

typedef struct {
    char signature[4]; 
    u32bit length;
    u8bit revision;
    u8bit checksum;
    char oem_id[6];
    char oem_table_id[8];
    u32bit oem_revision;
    u32bit creator_id;
    u32bit creator_revision;
} __attribute__((packed)) ACPISDTHeader;

typedef struct {
    ACPISDTHeader header;
    u32bit table_pointers[];  
} __attribute__((packed)) RSDT;

int acpi_checksum(void* base, u32bit length);
RSDPDescriptor* find_rsdp();
void parse_rsdt(RSDT* rsdt);
void acpi_init();