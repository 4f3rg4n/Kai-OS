#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "vga.h"
#include "../../libc/include/strings.h"

#define KEYBOARD_PORT 0x60

//keyboard symbols list
extern unsigned char symbols[256];

void init_keyboard();
char get_byte();
int get_char();

#endif