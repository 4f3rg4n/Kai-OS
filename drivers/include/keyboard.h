#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "vga.h"
#include "../../cpu/include/irq.h"
#include "../../libc/include/strings.h"
#include "../../debug/include/debug.h"

#define KEYBOARD_DATA_PORT 0x60

#define SYMBOLS_TABLE_SIZE 256
#define SYMBOLS_TABLE_TYPES 3
#define KEYBOARD_BUF_SIZE 1024

/* Keyboard control keys scancodes */
#define CTRL_CODE 0x1D
#define SHIFT_CODE 0x2A
#define ALT_CODE 0x38
#define CAPSLOCK_CODE 0x3A

#define RELEASE_CODE 0x80

#define IS_PRESSED(code, target_code, res) (res = (code == target_code ? 1 : 0))
#define IS_RELEASE(code, target_code, res) (res = (code == target_code ? 0 : 1))

/* Keyboard additional metadata struct */
typedef struct __attribute__((packed)){
    u8bit is_ctrl_pressed;
    u8bit is_shift_pressed;
    u8bit is_capslock_pressed;
    u8bit is_alt_pressed;
} keyboard_mdata;

/* Keyboard event struct */
typedef struct __attribute__((packed)){
    u8bit scancode;
    keyboard_mdata data;
} key_event;

//keyboard symbols list
extern unsigned char symbols[SYMBOLS_TABLE_TYPES][SYMBOLS_TABLE_SIZE];
extern key_event keyboard_buf[KEYBOARD_BUF_SIZE];
extern char* keys_buf[KEYBOARD_BUF_SIZE];
extern keyboard_mdata m_keyboard;
extern u32bit buf_ctr;

void keyboard_handler();
void keyboard_init();
void init_base_symbols(char* symbols);
void init_number_signs_symbols(char* symbols);
void init_capital_symbols(char* symbols);
int update_metadata(u8bit code);
int is_special_char(char ch);
int is_number(char ch);
int is_small_letter(char ch);
char key_to_ascii(key_event key);
int backspace();
void buf_cls();
u32bit get_buf(char* buf);
key_event get_last_event();
char get_char();
#endif