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

int gets(char* str){
    return get_buf(str);
}

void geti(int* var) {
    char buf[10] = {0};
    gets(buf);
    (*var) = atoi(buf);
}

int printf(char* format, void* arg) {
    int size = strsize(format);
    for(int i = 0; i < strsize(format) - 1; i++) {
        if(format[i] == '%') {
            format[i] = '\0';
            puts(format);
            switch (format[i + 1]) {
                case 's':
                    size += puts(arg) - 2;
                    break;
                case 'c':
                    putch((char)arg);
                    size--;
                    break;
                case 'd':        
                    size += puti(arg) - 2;
                    break;
                case 'x':
                    size += putx(arg) - 2;
                    break;
                case '%':
                    putch('%');
                    size--;
            }
            format += i + 2;              
        }
    }
    puts(format);

    return size;    
}

int puti(int var) {
    char num[20] = {0};
    int i = 0, size;

    if(var == 0) {
        puts("0");
        return 1;
    }

    for(; var != 0; i++, var /= 10)
        num[i] = (char)((var % 10) + 48);

    size = i;

    for(; i > 0; i--)
        putch(num[i - 1]);

    return size;
}
int putx(unsigned int var) {
    char* hex = "0123456789abcdef";
    char num[20] = {0};
    int size = 0, i = 0;

    while(var != 0) {
        u8bit half_byte = var &0xf;
        num[i] = hex[half_byte];
        var = var >> 4;
        i++;
    }

    size = i;

    for(; i > 0; i--)
        putch(num[i - 1]);

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
