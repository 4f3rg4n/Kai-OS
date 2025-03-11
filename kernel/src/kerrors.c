#include "../include/kerrors.h"

void panic(char* err) {
    printf("panic: %s\n", err);
    __asm__ __volatile__("error: jmp error");
}

void alert(char* msg) {
    puts_c(msg, 0x04);
    putch('\n');
}