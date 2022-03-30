#include "timer.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "../drivers/ports.h"

uint32_t tick = 0;

void timer_interrupt_handler(registers_t *regs) {
    tick++;
}


void init_timer(uint32_t freq) {
    set_interrupt_handler(TIMER_INTERRUPT, timer_interrupt_handler);

    uint32_t d = 1193180 / freq;

    write_bytes_to_port(0x43, 0x36);
    write_bytes_to_port(0x40, (uint8_t)(d & 0xFF));
    write_bytes_to_port(0x40, (uint8_t)((d >> 8) & 0xFF));
}