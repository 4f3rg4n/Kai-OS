#include "../libs/include/stdlib.h"
#include "../libs/include/memory.h"
#include "../libs/include/strings.h"

void kernel_main() {
    cls();
    keyboard();
    char str1[10];
    char str2[10] = "abc\0";
    puts(strcpy(str1, str2));
    puts(str1);
    puts("Welcome to Kai-OS!\n\0");
}
