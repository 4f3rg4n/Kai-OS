#include "io.h"
#include "vga.h"

#define KEYBOARD_PORT 0x60

unsigned char symbols[256];

void init_keyboard();
char get_byte();
int get_char();
