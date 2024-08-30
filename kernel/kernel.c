#include "../libs/include/stdlib.h"
#include "../libs/include/memory.h"
#include "../libs/include/strings.h"
#include "cpu/include/idt.h"
#include "cpu/include/isr.h"

void kmain() {
    cls();
    puts_c("init keyboard\n", 0x0A);
    keyboard();
    puts_c("init idt\n", 0x0A);
    idt_init();
    puts_c("init isr\n", 0x0A);
    isr_init();
    asm volatile ("int $21");  // Trigger interrupt 1 manually
    puts("Welcome to Kai-OS!\n\0");
}
