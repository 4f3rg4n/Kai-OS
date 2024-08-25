#include "io.h"

#define KEYBOARD_PORT 0x60

enum numbers {
    n0 = 0x30,
    n1, 
    n2,
    n3,
    n4,
    n5,
    n6,
    n7,
    n8,
    n9
};

char get_byte();
int get_char();
