#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "vga.h"
#include "../../libc/include/strings.h"
#include "../../debug/include/debug.h"

#define KEYBOARD_PORT 0x60

//keyboard symbols list
extern unsigned char symbols[256];

void keyboard_init();
int backspace();
char get_byte();
int get_char();

#endif