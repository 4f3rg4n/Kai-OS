#include "../include/isr.h"

const char *isr_desc[] = {
    "Division By Zero\0",
    "Debug",
    "Divide By Zero Error",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device not available",
    "Double Fault",
    "Unused",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Unused",
    "x87 FPU error",
    "Alignment Check",
    "Machine Check",
    "SIMD (SSE/AVX) error",
};

void isr_init() {
    idt_set_new_gate(0, (u32bit)isr0, 0x08, 0x8E);
    idt_set_new_gate(1, (u32bit)isr1, 0x08, 0x8E);
}

void isr_handler(u16bit entry) {
    puts_c("alert: \0", 0x04);
    puts_c(isr_desc[entry]);
    puts("\n\0");
}