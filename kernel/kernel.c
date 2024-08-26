#include "../libs/include/stdlib.h"
#include "../libs/include/memory.h"
#include "../libs/include/strings.h"

void kernel_main() {
    cls();
    keyboard();
    char str1[10] = "noam\0";
    char str2[10] = "no\0";
    putch(strsize(str1) + 97);
    puts("Welcome to Kai-OS!\n\0");
}
