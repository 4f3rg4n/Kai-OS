#ifndef TIMER_H
#define TIMER_H

#include "irq.h"
#include "../../debug/debug.h"

#define TIMER_HANDLER_OFFSET 0

extern u32bit ticks;

void timer_handler();
void timer_init();
void timer_delay(u32bit delay_ticks);

#endif