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
    irq_set_handler(irq00_offset, timer_handler);

#ifdef DBG
    puts_c("Timer initialized successfully\n", 0x0A);
#endif
}

void timer_set_frequency(u32bit frq) {
    if (frq == 0) {
        puts("Error: Frequency must be greater than zero\n");
        return;
    }
    frequency = frq;

    // Calculate the divisor
    u32bit divisor = PIT_BASE_FREQUENCY / frequency;

    // Send the command to the PIT
    out8(TIMER_COMMAND_PORT, PIT_MODE3_COMMAND); // Command for square wave mode

    // Send the divisor to the PIT (low byte first, then high byte)
    out16(TIMER_DATA_PORT, divisor);
}

void timer_delay(u32bit delay_ticks) {
    u32bit target_ticks = ticks + delay_ticks;
    while (ticks < target_ticks) {
        // Wait until the desired number of ticks has passed
    }
}

void timer_print() {
    puts("\nTicks: ");
    printf("%d", ticks);
    puts("\n");
}
