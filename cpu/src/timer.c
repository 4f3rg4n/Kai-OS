#include "../include/timer.h"

u32bit ticks = 0; // Counter for timer ticks
u32bit frequency = 18; // Default frequency

void timer_handler() {
    ticks++;
    if (ticks % frequency == 0) {
        ticks = 0;
    }
}

void timer_init() {
    if (frequency == 0) {
        puts("Error: Timer frequency cannot be zero\n");
        return;
    }
    // Set the frequency
    //timer_set_frequency(1000); // Example: 1000 Hz for 1 ms intervals

    // Register the IRQ handler
    irq_set_handler(timer_irq, timer_handler);

    dbg_ok("timer init successfully\n");
}

void timer_set_frequency(u32bit frq) {
    if (frq == 0) {
        dbg_alert("Error: Frequency must be greater than zero\n");
        return;
    }

    // Calculate the divisor
    u32bit divisor = PIT_BASE_FREQUENCY / frequency;

    // Send the command to the PIT
    //out8(TIMER_COMMAND_PORT, PIT_MODE3_COMMAND); // Command for square wave mode

    // Send the divisor to the PIT (low byte first, then high byte)
    out16(TIMER_DATA_PORT, divisor);

    frequency = frq;
}

void timer_delay(u32bit delay_ticks) {
    u32bit ctr = 0, temp_tick = 0;

    while (ctr != delay_ticks){
        temp_tick = ticks; // get current ticks
        while (ticks != (temp_tick + 1) % frequency){} // wait one timer tick
        ctr++;
    }
}

void timer_print() {
    puts("\nTicks: ");
    printf("%d", ticks);
    puts("\n");
}
