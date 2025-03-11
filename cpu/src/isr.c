#include "../include/isr.h"

const char *isr_desc[] = {
    "Division By Zero",
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
    "Page Fault",//"Segment Not Present",
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

/* init basic isr's into the IDT */
void isr_init() {
    idt_set_new_gate(0,  (u32bit)isr00, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(1,  (u32bit)isr01, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(2,  (u32bit)isr02, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(3,  (u32bit)isr03, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(4,  (u32bit)isr04, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(5,  (u32bit)isr05, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(6,  (u32bit)isr06, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(7,  (u32bit)isr07, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(8,  (u32bit)isr08, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(9,  (u32bit)isr09, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(10, (u32bit)isr10, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(11, (u32bit)isr11, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(12, (u32bit)isr12, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(13, (u32bit)isr13, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(14, (u32bit)isr14, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(15, (u32bit)isr15, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(16, (u32bit)isr16, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(17, (u32bit)isr17, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(18, (u32bit)isr18, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(19, (u32bit)isr19, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(20, (u32bit)isr20, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(21, (u32bit)isr21, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(22, (u32bit)isr22, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(23, (u32bit)isr23, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(24, (u32bit)isr24, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(25, (u32bit)isr25, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(26, (u32bit)isr26, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(27, (u32bit)isr27, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(28, (u32bit)isr28, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(29, (u32bit)isr29, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(30, (u32bit)isr30, KERNEL_CS, INTERRUPT_GATE);
    idt_set_new_gate(31, (u32bit)isr31, KERNEL_CS, INTERRUPT_GATE);

    dbg_ok("ISR init successfully\n");
}

/* Global Handling isr's */
void isr_handler(u16bit entry) {
    puts("alert: \0");
    alert(isr_desc[entry]);
}