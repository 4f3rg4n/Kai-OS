#ifndef DBG_H
#define DBG_H

#include "../../libc/include/strings.h"

#define DBG

void dbg_ok(char* dbg_msg);
void dbg_err(char* dbg_msg);
void dbg_alert(char* dbg_msg);

#endif
