#include "../include/vga.h"

char (*screen)[WIDTH] = (char(*)[WIDTH])VGA_ADDR;
short row = 0;
short col = 0;
char default_color = 0x0F;

void vga_putch(char ch, char color){
    if(!color)
        color = default_color;

    screen[row][col] = ch;
    screen[row][col + 1] = color;
    col += 2;

    if(col == WIDTH)
        vga_next_line();
}

void vga_next_line(){
    col = 0;
    row++;

    if(row == HEIGHT){
        vga_clean_screen();
        row = 0;
    }
}

void vga_set(short row, short col, char ch){
    screen[row][col] = ch;
}

char vga_get(short row, short col){
    return screen[row][col];
}

void vga_clean_screen(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++)
            screen[i][j] = '\0';        
    }
    col = 0;
    row = 0;
}
