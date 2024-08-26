#include "../include/string.h"

int strcmp (const char* str1, const char* str2){
    for(int i = 0; 1==1; i++) {
        if(str1[i] == '\0' || str2[i] == '\0')
            return 0;
        if (str1[i] < str2[i])
            return -1;
        else if(str1[i] > str2[i])
            return 1;
    }
}

int strsize(const char* str1){
    int i = 0;
    for(i = 0; str1[i] != '\0'; i++){}
    return i;
}


char* strcpy(char* dst, const char* src) {
    int i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while(src[i] != '\0');

    return dst;
}

char* strcat(char* dst, const char* src) {
    int i = 0, j = 0;
    while(dst[i] != '\0'){ i++; }
    do{ 
        dst[i] = src[j]; 
        j++;
        i++;
    } while(src[j] != '\0');

    return dst;
}

void puts(const char* str){
    for (int i = 0; str[i] != '\0'; i++){
        if(str[i] == '\n'){
            vga_next_line();
            continue;
        }
        putch(str[i]);
    }
}
