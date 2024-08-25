#include "../include/stdlib.h"

void keyboard() {
    init_keyboard();
}

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
    vga_clean_screen();
}

char getch(){
    return get_char();
}

void gets(char* str){
    char c = 0;
    for(int i = 0; 1==1; i++) {
        c = getch();
        getch();
        if(c == '\n') {
            str[i] = '\0';
            break;
        }
        putch(c);
        str[i] = c;
    }
}