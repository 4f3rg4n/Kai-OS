#include "../include/vga.h"

char (*screen)[HEIGHT] = (char(*)[HEIGHT])VGA_ADDR;
short row = 0;
short col = 0;
char color = 0x0F;

void vga_putch(char ch){
    screen[row][col] = ch;
    screen[row][col + 1] = color;
    col += 2;

    if(col == WIDTH)
        vga_next_line();
}

void vga_next_line(){
    col = 0;
    row++;
}

void vga_set(short row, short col, char ch){
    screen[row][col] = ch;
}

char vga_get(short row, short col){
    return screen[row][col];
}

void vga_cls(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++)
            screen[i][j] = '\0';        
    }
}
