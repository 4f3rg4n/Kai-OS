#ifndef STDLIB_H
#define STDLIB_H

#include "../../drivers/include/vga.h"
#include "../../drivers/include/keyboard.h"

void keyboard();
void putch(char ch);
void putch_c(char ch, char color);
void cls();
char getch();
void gets(char* str);
void geti(int* var);
int puti(int var);
int atoi(char* str);

#endif