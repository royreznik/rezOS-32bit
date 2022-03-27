#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/types.h"

int main() {
    clear_screen();
    for (uint8_t i = 0; i < 25; ++i) {
        char str[255];
        i_to_a(i, str);
        kprint_at(str, 0, i);
    }
    kprint("\nNoice");
    return 0;
}
