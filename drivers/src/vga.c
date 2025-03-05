#include "../include/vga.h"

/* Screen settings */
char (*screen)[WIDTH] = (char(*)[WIDTH])VGA_ADDR;
short row = 0;
short col = 0;
char default_color = 0x0F;

void vga_putch(char ch, char color){
    //check if the char is just new enter line
    if(ch == '\n') {
        vga_next_line();
        return;
    }

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
    screen[row][col + 1] = default_color;
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

void vga_back() {
    vga_set(row, col, 0);

    //check if the cursor isn't at the beginning of the line
    if(col != 0) {
        col -= 2;
    }
    else {
        if(row != 0){ //check if the cursor isn't at the beginning of the screen
            row--;
            col = WIDTH - 2;
        }
    }

    vga_set(row, col, '\0'); //set the current char to null (clean it)
}
