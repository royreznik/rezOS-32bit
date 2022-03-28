#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/isr.h"

int main() {
    clear_screen();
    initialize_isr();
    for (uint8_t i = 0; i < 25; ++i) {
        char str[255];
        i_to_a(i, str);
        kprint_at(str, 0, i);
    }
    __asm__ __volatile__("int $31");
    return 0;
}
