#include "../drivers/screen.h"
//#include "utils.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

int main() {
    initialize_isr();
    __asm__ __volatile__("sti");
    init_timer(50);
    return 0;
}
