#ifndef TIMER_H
#define TIMER_H

#include "irq.h"
#include "../../debug/include/debug.h"
#include "../../libc/include/strings.h"
#include "../../libc/include/stdlib.h"

#define PIT_BASE_FREQUENCY 0x1234de // set by default in PC hardware by IBM .

#define TIMER_COMMAND_PORT 0x43 // command port to communicate with the timer.
#define TIMER_DATA_PORT 0x40 // get data port from timer.

#define PIT_MODE3_COMMAND 0x36 // square wave mode.

/* clock data struct */
typedef struct __attribute__((packed)) {
    u8bit seconds;
    u8bit minutes;
    u8bit hours;
    u32bit row;
    u32bit col;
    u8bit isActive;
} clock_data;

extern u32bit ticks; //timer ticks counter
extern u32bit frequency; //frequency of the timer
extern clock_data clock; //clock format hh:mm:ss



void timer_handler();
void timer_init();
void init_timer(u32bit frequency);
void timer_delay(u32bit delay_ticks);
void timer_set_frequency(u32bit frq);
void fixed_time(u8bit* time);
void timer_print();
void clock_print();

#endif