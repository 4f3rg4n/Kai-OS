#ifndef VGH_H
#define VGA_H

#define VGA_ADDR 0xb8000
#define WIDTH 160
#define HEIGHT 25

extern char (*screen)[WIDTH];
extern short row;
extern short col;
extern char default_color;

void vga_putch(char ch, char color);
void vga_next_line();
void vga_set(short row, short col, char ch);
char vga_get(short row, short col);
void vga_clean_screen();
void vga_back();

#endif