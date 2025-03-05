#include "../include/debug.h"

/* 
* Debug Messages: 
* ok - green: log message
* err - red: error message
* alert - red: alert message (Note: alert is not a error message)
*/

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
