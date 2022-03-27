#include "utils.h"


void mem_copy(int8_t *source, int8_t *dest, int nbytes) {
    for (int i = 0; i < nbytes; ++i) {
        *(dest + i) = *(source + i);
    }
}


void i_to_a(int n, char str[]) {
    int i = 0;
    int sign = (n < 0);
    if (sign) {
        n = -n;
    }
    do {
        str[i++] = n % 10 + '0';
    } while((n /= 10) > 0);

    if (sign) {
        str[i++] = '-';
    }
    str[i] = '\0';
}