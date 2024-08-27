#ifndef STDLIB_H
#define STDLIB_H

#include "../../drivers/include/vga.h"
#include "../../drivers/include/keyboard.h"

void keyboard();
void putch(char ch);
void cls();
char getch();
void gets(char* str);
int atoi(char* str);

#endif