#include "../include/debug.h"

void dbg_ok(char* dbg_msg) {
    #ifdef DBG
    puts_c(dbg_msg, 0x0A);
    #endif
}

void dbg_err(char* dbg_msg) {
    #ifdef DBG
    puts_c(dbg_msg, 0x04);
    #endif
}

void dbg_alert(char* dbg_msg) {
    puts_c(dbg_msg, 0x04);
}
