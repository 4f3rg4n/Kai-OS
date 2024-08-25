#include "../libs/include/stdlib.h"
#include "../libs/include/mem.h"

void kernel_main() {
    cls();
    keyboard();
    char str1[10] = "noam\0";
    char str2[10] = "naam\0";
    putch(memcmp(str1, str2, 2) + 98);
    print("Welcome to Kai-OS!\n\0");
}
