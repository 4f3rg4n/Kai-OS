#include "../include/string.h"

/*
int strcmp (const char* str1, const char* str2){

}

int strlen(const char* str){

}

char* strcpy(char* dst, const char* src){

}

char *strcat(char *dst, const char *src){

}
*/
void puts(const char* str){
    for (int i = 0; str[i] != '\0'; i++){
        if(str[i] == '\n'){
            vga_next_line();
            continue;
        }
        putch(str[i]);
    }
}
