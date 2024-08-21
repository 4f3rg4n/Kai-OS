#include "../include/stdlib.h"

void putch(char ch){
    vga_putch(ch);
}

void print(char* msg){
    for (int i = 0; msg[i] != '\0'; i++){
        if(msg[i] == '\n'){
            vga_next_line();
            continue;
        }
        putch(msg[i]);
    }

}

void cls(){
    vga_cls();
}