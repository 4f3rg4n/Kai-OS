#include "../include/timer.h"

u32bit ticks = 0;
u32bit frequency = 18;

void timer_handler() {
    ticks += 1;

    if (ticks % frequency == 0) {
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

void timer_set_frequency(u32bit frq) {
    frequency = frq;
    u32bit divisor = PIT_BASE_FREQUENCY / frequency; // calculate the timer divisor
    out8(TIMER_COMMAND_PORT, PIT_MODE3_COMMAND); // send timer command 3 (square wave)
    out16(TIMER_DATA_PORT, divisor); // set new timer divisor
}

void timer_print() {
    printf("%s", "\nticks: ");
    printf("%d", ticks);
    printf("%s", "\n");
}