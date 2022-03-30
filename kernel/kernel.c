#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

int main() {
    initialize_isr();
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
    return 0;
}
