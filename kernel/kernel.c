#include "../libc/include/stdlib.h"
#include "../libc/include/memory.h"
#include "../libc/include/strings.h"
#include "../cpu/include/idt.h"
#include "../cpu/include/isr.h"

void kmain() {
    char name[10];
    cls();

    keyboard();
    idt_init();
    isr_init();

    puts("name: ");
    gets(name);
    puts("\nHey ");
    puts(name);
    puts(" Welcome to Kai-OS!\n");
}
