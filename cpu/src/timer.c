#include "../include/timer.h"

u32bit ticks = 0; // Counter for timer ticks
u32bit frequency = 18; // Default frequency
clock_data* clock;

void timer_handler() {
    ticks++;
    clock_print();
    if (ticks % frequency == 0) {
        ticks = 0;
        clock->seconds++;
        if(clock->seconds % 60 == 0){
            clock->seconds = 0;
            clock->minutes++;
            if(clock->minutes % 60 == 0){
                clock->minutes = 0;
                clock->hours++;
                if(clock->hours % 24 == 0){
                    clock->hours = 0;
                }
            }
        }               
    }
}

void timer_init() {
    clock->seconds = 0;
    clock->minutes = 0;
    clock->hours = 0;
    clock->row = 0;
    clock->col = 144;
    clock->isActive = 1;

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

void fixed_time(u8bit time[]) {
    if((*time) % 60 == 0) {
        time[0] = 0;
        time[1]++;
    }
}

void timer_print() {
    puts("\nTicks: ");
    puti(ticks);
    putch('\n');
}

void clock_print() {
    if(!clock->isActive)
        return;

    u32bit row = clock->row, col = clock->col;

    //print seconds
    vga_set(row, col + 14, (clock->seconds % 10) + '0');
    vga_set(row, col + 12, (clock->seconds / 10) + '0');
    vga_set(row, col + 10, ':');

    //print minutes
    vga_set(row, col + 8, (clock->minutes % 10) + '0');
    vga_set(row, col + 6, (clock->minutes / 10) + '0');
    vga_set(row, col + 4, ':');

    //print hours
    vga_set(row, col + 2, (clock->hours % 10) + '0');
    vga_set(row, col + 0, (clock->hours / 10) + '0');
}
