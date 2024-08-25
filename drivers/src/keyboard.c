#include "../include/keyboard.h"

char get_byte(){
    return in8(KEYBOARD_PORT);
}

int get_char() {
    char c;

    while ((in8(0x64) & 1) == 0); // Check if the output buffer is full (bit 0 of port 0x64 is set)
    c = get_byte();

    switch (c) {
        case 0x02:
            return n1;
        case 0x03:
            return n2;
        case 0x04:
            return n3;
        case 0x05:
            return n4;
        case 0x06:
            return n5;
        case 0x07:
            return n6;
        case 0x08:
            return n7;
        case 0x09:
            return n8;
        case 0x0A:
            return n9;
        case 0x0B:
            return n0;
    
    default:
        break;
    }
    return c;
}