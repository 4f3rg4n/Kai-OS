#include "../include/stdlib.h"

void keyboard() {
    init_keyboard();
}

void putch(char ch){
    vga_putch(ch);
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

int atoi(char* str) {
    int res = 0;
    for(int i = 0; 1==1; i++){
        if(str[i] == '\0')
            break;
        res *= 10;
        res += str[i] - 0x30;        
    }

    return res;
}
