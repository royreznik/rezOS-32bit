#include "mem.h"


void mem_copy(int8_t *source, int8_t *dest, int nbytes) {
    for (int i = 0; i < nbytes; ++i) {
        *(dest + i) = *(source + i);
    }
}

void mem_set(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t* tmp = (uint8_t*) dest;
    for(; len != 0; --len) {
        *tmp++ = val;
    }
}
