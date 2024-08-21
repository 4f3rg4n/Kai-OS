#define VGA_ADDR 0xb8000
#define WIDTH 160
#define HEIGHT 160

void vga_putch(char ch);
void vga_next_line();
void vga_set(short row, short col, char ch);
char vga_get(short row, short col);
void vga_cls();