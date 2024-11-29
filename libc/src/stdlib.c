#include "../include/stdlib.h"

void keyboard() {
    keyboard_init();
}

void putch(char ch){
    vga_putch(ch, 0);
}

void putch_c(char ch, char color){
    vga_putch(ch, color);
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

        if(c == 0) {
            vga_back();
            if(i) {                
                i--;
                str[i] = '\0';
            } 
        }
        else {
            putch(c);
            str[i] = c;
        }
    }
}

void geti(int* var) {
    char buf[10] = {0};
    gets(buf);
    (*var) = atoi(buf);
}

int printf(char* format, void* data) {
    int size = 0;

    if(!strcmp(format, "%s"))
        size = puts((char*)data);
    else if(!strcmp(format, "%d"))
        size = puti((int)data);
    
    return size;
}

int puti(int var) {
    char num[20] = {0};
    int i = 0, size;

    for(; var != 0; i++, var /= 10)
        num[i] = (char)((var % 10) + 48);

    size = i;

    for(; i >= 0; i--)
        putch(num[i]);

    return size;
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
