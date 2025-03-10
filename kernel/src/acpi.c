#include "../include/acpi.h"

int acpi_checksum(void* base, u32bit length) {
    u8bit sum = 0;
    for (u32bit i = 0; i < length; i++) {
        sum += ((u8bit*)base)[i];
    }
    return sum == 0;
}

RSDPDescriptor* find_rsdp() {
    for (u32bit* addr = RSDP_SEARCH_START; addr < RSDP_SEARCH_END; addr += 16) {
        RSDPDescriptor* rsdp = (RSDPDescriptor*)addr;
        if (memcmp(rsdp->signature, "RSD PTR ", 8) == 0 && acpi_checksum(rsdp, sizeof(RSDPDescriptor))) {
            return rsdp;
        }
    }
    return nullptr;
}

void parse_rsdt(RSDT* rsdt) {
    int entry_count = (rsdt->header.length - sizeof(ACPISDTHeader)) / 4;
    for (int i = 0; i < entry_count; i++) {
        ACPISDTHeader* table = (ACPISDTHeader*)(u32bit*)rsdt->table_pointers[i];
        if (memcmp(table->signature, "FACP", 4) == 0) {
            // Found FADT (Fixed ACPI Description Table)
            printf("Found FADT at 0x%x\n", (u32bit)table);
        } else if (memcmp(table->signature, "APIC", 4) == 0) {
            // Found MADT (Multiple APIC Description Table)
            printf("Found MADT at 0x%x\n", (u32bit)table);
        }
    }
}

void acpi_init() {
    RSDPDescriptor* rsdp = find_rsdp();
    if (!rsdp) {
        printf("ACPI RSDP not found!\n");
        return;
    }

    printf("RSDP found at: 0x%x\n", (u32bit)rsdp);
    
    RSDT* rsdt = (RSDT*)(u32bit*)rsdp->rsdt_address;
    if (!acpi_checksum(rsdt, rsdt->header.length)) {
        printf("Invalid RSDT checksum!\n");
        return;
    }

    parse_rsdt(rsdt);
}
