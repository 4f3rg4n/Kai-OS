#include "../include/kerrors.h"

void panic(char* err) {
    printf("panic: %s\n", err);
    __asm__ __volatile__("_panic: jmp _panic");
}

void abort(char* func, char* err) {
    printf("abort: %s - ", func);
    printf("%s\n", err);
    __asm__ __volatile__("_abort: jmp _abort");
}

void alert(char* msg) {
    puts_c(msg, 0x04);
    putch('\n');
}
