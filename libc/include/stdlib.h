#ifndef STDLIB_H
#define STDLIB_H

#include "../../drivers/include/vga.h"
#include "../../drivers/include/keyboard.h"

void keyboard();
void putch(char ch);
void putch_c(char ch, char color);
int printf(char* format, void* arg);
void cls();
char getch();
int gets(char* str);
void geti(int* var);
int puti(int var);
int putx(unsigned int var);
int atoi(char* str);

#endif