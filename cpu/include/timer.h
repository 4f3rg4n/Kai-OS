#ifndef TIMER_H
#define TIMER_H

#include "irq.h"
#include "../../debug/include/debug.h"
#include "../../libc/include/strings.h"
#include "../../libc/include/stdlib.h"

#define TIMER_HANDLER_OFFSET 32 // offset in PIC irq's.
#define PIT_BASE_FREQUENCY 0x1234de // set by default in PC hardware by IBM .

#define TIMER_COMMAND_PORT 0x43 // command port to communicate with the timer.
#define TIMER_DATA_PORT 0x40 // get data port from timer.

#define PIT_MODE3_COMMAND 0x36 // square wave mode.

extern u32bit ticks;
extern u32bit frequency;

void timer_handler();
void timer_init();
void init_timer(u32bit frequency);
void timer_delay(u32bit delay_ticks);
void timer_set_frequency(u32bit frq);
void timer_print();

#endif