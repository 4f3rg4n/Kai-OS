#include "../include/keyboard.h"

//keyboard symbols list
unsigned char symbols[256] = {0};

void keyboard_init() {
    symbols[0x2] = '1'; 
    symbols[0x3] = '2'; 
    symbols[0x4] = '3';
    symbols[0x5] = '4'; 
    symbols[0x6] = '5'; 
    symbols[0x7] = '6';
    symbols[0x8] = '7'; 
    symbols[0x9] = '8'; 
    symbols[0xA] = '9';
    symbols[0xB] = '0';
    symbols[0x1E] = 'a'; 
    symbols[0x30] = 'b'; 
    symbols[0x2E] = 'c';
    symbols[0x20] = 'd';  
    symbols[0x12] = 'e'; 
    symbols[0x21] = 'f';
    symbols[0x22] = 'g'; 
    symbols[0x23] = 'h'; 
    symbols[0x17] = 'i';
    symbols[0x24] = 'j';
    symbols[0x25] = 'k';
    symbols[0x26] = 'l';  
    symbols[0x32] = 'm';
    symbols[0x31] = 'n'; 
    symbols[0x18] = 'o'; 
    symbols[0x19] = 'p'; 
    symbols[0x10] = 'q'; 
    symbols[0x13] = 'r'; 
    symbols[0x1F] = 's'; 
    symbols[0x14] = 't';
    symbols[0x16] = 'u'; 
    symbols[0x2F] = 'v';
    symbols[0x11] = 'w';
    symbols[0x2D] = 'x';
    symbols[0x15] = 'y';  
    symbols[0x2C] = 'z';
    symbols[0xC] = '-'; 
    symbols[0xD] = '=';
    symbols[0x1A] = '[';
    symbols[0x1B] = ']'; 
    symbols[0x1C] = '\n'; 
    symbols[0x27] = ';';
    symbols[0x28] = '\''; 
    symbols[0x29] = '~'; 
    symbols[0x33] = ','; 
    symbols[0x34] = '.'; 
    symbols[0x35] = '/';
    symbols[0x39] = ' ';
    symbols[0x0d] = 0;

    dbg_ok("keyboard init successfully\n");
}

int backspace() {
    vga_back();
}

char get_byte(){
    return in8(KEYBOARD_PORT);
}

int get_char() {
    char c;

    while ((in8(0x64) & 1) == 0); //wait until buffer is empty
    c = get_byte();

    //check if there is exist symbol for this char
    if(symbols[(int)c])
        return symbols[(int)c];
    return c;
}
