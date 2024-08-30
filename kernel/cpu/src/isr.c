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
    idt_set_new_gate(2, (u32bit)isr2, 0x08, 0x8E);
    idt_set_new_gate(3, (u32bit)isr3, 0x08, 0x8E);
    idt_set_new_gate(4, (u32bit)isr4, 0x08, 0x8E);
    idt_set_new_gate(5, (u32bit)isr5, 0x08, 0x8E);
    idt_set_new_gate(6, (u32bit)isr6, 0x08, 0x8E);
    idt_set_new_gate(7, (u32bit)isr7, 0x08, 0x8E);
    idt_set_new_gate(8, (u32bit)isr8, 0x08, 0x8E);
    idt_set_new_gate(9, (u32bit)isr9, 0x08, 0x8E);
    idt_set_new_gate(10, (u32bit)isr10, 0x08, 0x8E);
    idt_set_new_gate(11, (u32bit)isr11, 0x08, 0x8E);
    idt_set_new_gate(12, (u32bit)isr12, 0x08, 0x8E);
    idt_set_new_gate(13, (u32bit)isr13, 0x08, 0x8E);
    idt_set_new_gate(14, (u32bit)isr14, 0x08, 0x8E);
    idt_set_new_gate(15, (u32bit)isr15, 0x08, 0x8E);
    idt_set_new_gate(16, (u32bit)isr16, 0x08, 0x8E);
    idt_set_new_gate(17, (u32bit)isr17, 0x08, 0x8E);
    idt_set_new_gate(18, (u32bit)isr18, 0x08, 0x8E);
    idt_set_new_gate(19, (u32bit)isr19, 0x08, 0x8E);
    idt_set_new_gate(20, (u32bit)isr20, 0x08, 0x8E);
    idt_set_new_gate(21, (u32bit)isr21, 0x08, 0x8E);
    idt_set_new_gate(22, (u32bit)isr22, 0x08, 0x8E);
}

void isr_handler(u16bit entry) {
    puts_c("alert: \0", 0x04);
    puts_c(isr_desc[entry]);
    puts("\n\0");
}