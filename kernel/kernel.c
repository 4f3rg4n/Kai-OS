#include "../libs/include/stdlib.h"
#include "../libs/include/mem.h"
#include "../libs/include/strings.h"

void kernel_main() {
    cls();
    keyboard();
    char str1[10] = "noam\0";
    char str2[10] = "no\0";
    putch(strcmp(str1, str2) + 98);
    puts("Welcome to Kai-OS!\n\0");
}
