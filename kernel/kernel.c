#include "../drivers/screen.h"
#include "utils.h"

int main() {
    clear_screen();
    for (int i = 0; i < 25; ++i) {
        char str[255];
        i_to_a(i, str);
        kprint_at(str, 0, i);
    }
    kprint("\nNoice");
    return 0;
}
