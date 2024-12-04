#include "../include/timer.h"
#include "../../libc/include/strings.h"

u32bit ticks = 0;

void timer_handler() {
    ticks++;

    if (ticks % 18 == 0)
    {
        puts("One second has passed\n");
    }
}

void timer_init() {
    irq_set_handler(TIMER_HANDLER_OFFSET, timer_handler);

    #ifdef DBG
    puts_c("timer init successfully\n", 0x0A);
    #endif
}

void timer_delay(u32bit delay_ticks) {
    u32bit time = delay_ticks + ticks;
    while(ticks < time){};
}
