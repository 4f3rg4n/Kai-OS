#ifndef TIMER_H
#define TIMER_H

#include "irq.h"
#include "../../debug/debug.h"

#define TIMER_HANDLER_OFFSET 0

extern u32bit ticks;
extern u32bit frequency;

void timer_handler();
void timer_init();
void timer_delay(u32bit delay_ticks);
void timer_set_frequency(u32bit frq);

#endif