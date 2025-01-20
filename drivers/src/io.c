#include "../include/io.h"

u8bit in8(short port) {
    unsigned char result;
    __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

u16bit in16(short port) {
    unsigned short result;
    __asm__ ("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

u32bit in32(short port) {
    unsigned int result;
    __asm__ ("in %%dx, %%eax" : "=a" (result) : "d" (port));
    return result;
}

void out8(short port, char byte) {
    __asm__ ("out %%al, %%dx" : : "a" (byte), "d" (port));
}

void out16(short port, char byte) {
    __asm__ ("out %%ax, %%dx" : : "a" (byte), "d" (port));
}

void out32(short port, int word) {
    __asm__ ("out %%eax, %%dx" : : "a" (word), "d" (port));
}
