#include "../include/gdt.h"

void gdt_init() {

}

void gdt_load(gdtr* gdtr) {
    __asm__ __volatile__("lgdt (%0)" : : "r" (gdtr));
}
