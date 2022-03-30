#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

int main() {
    initialize_isr();
    // asm volatile ("int $0x10");
    __asm__ __volatile__("sti");
    init_timer(1000);

    kprint("Hello World!!\n");

    sleep(5000);

    kprint("BIE World!!\n");

    // sleep(50000);


    // uint32_t time = 0;


    // for(int i = 0; i < 10; i++)
    //     for(int j = 0; j < 10; j++) ;
    // time = getTime();

    // char str[256];
    // i_to_a(time, str);
    // kprint(str);
    // kprint("\n");


    // kprint("Tick: ");
    // char str[256];
    // i_to_a(tick, str);
    // kprint(str);
    // kprint("\n");

    return 0;
}
