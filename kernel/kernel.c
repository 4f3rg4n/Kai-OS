#include "../libs/include/stdlib.h"

void kernel_main() {
    cls();
    print("Welcome to Kai-OS!\n\0");
    print("letter: ");
    char letter = get_char();
    print("\nyour letter is: ");
    putch(letter);
}
