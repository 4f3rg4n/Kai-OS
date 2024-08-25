#include "../libs/include/stdlib.h"

void kernel_main() {
    char str[10];
    cls();
    keyboard();
    print("Welcome to Kai-OS!\n\0");
    print("string: ");
    gets(str);
    print("\nyour string is: ");
    print(str);
}
