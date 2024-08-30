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
    "Coprocessor Segment Overrun",
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
    "Virtualization Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_init() {
    idt_set_new_gate(0,  (u32bit)isr0,  0x08, 0x8E);
    idt_set_new_gate(1,  (u32bit)isr1,  0x08, 0x8E);
    idt_set_new_gate(2,  (u32bit)isr2,  0x08, 0x8E);
    idt_set_new_gate(3,  (u32bit)isr3,  0x08, 0x8E);
    idt_set_new_gate(4,  (u32bit)isr4,  0x08, 0x8E);
    idt_set_new_gate(5,  (u32bit)isr5,  0x08, 0x8E);
    idt_set_new_gate(6,  (u32bit)isr6,  0x08, 0x8E);
    idt_set_new_gate(7,  (u32bit)isr7,  0x08, 0x8E);
    idt_set_new_gate(8,  (u32bit)isr8,  0x08, 0x8E);
    idt_set_new_gate(9,  (u32bit)isr9,  0x08, 0x8E);
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
    idt_set_new_gate(23, (u32bit)isr23, 0x08, 0x8E);
    idt_set_new_gate(24, (u32bit)isr24, 0x08, 0x8E);
    idt_set_new_gate(25, (u32bit)isr25, 0x08, 0x8E);
    idt_set_new_gate(26, (u32bit)isr26, 0x08, 0x8E);
    idt_set_new_gate(27, (u32bit)isr27, 0x08, 0x8E);
    idt_set_new_gate(28, (u32bit)isr28, 0x08, 0x8E);
    idt_set_new_gate(29, (u32bit)isr29, 0x08, 0x8E);
    idt_set_new_gate(30, (u32bit)isr30, 0x08, 0x8E);
    idt_set_new_gate(31, (u32bit)isr31, 0x08, 0x8E);
}

void isr_handler(u16bit entry) {
    puts_c("alert: \0", 0x04);
    puts_c(isr_desc[entry]);
    puts("\n\0");
}