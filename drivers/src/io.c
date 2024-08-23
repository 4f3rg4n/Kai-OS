#include "../include/io.h"

char in8(short port) {
    unsigned char result;
    __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

int in32(short port) {
    unsigned int result;
    __asm__ ("in %%dx, %%eax" : "=a" (result) : "d" (port));
    return result;
}

void out8(short port, char byte) {
    __asm__ ("out %%al, %%dx" : : "a" (byte), "d" (port));
}

void out32(short port, int word) {
    __asm__ ("out %%eax, %%dx" : : "a" (word), "d" (port));
}
