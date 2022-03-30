#include "utils.h"


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
    str_rev(str);
}

void str_rev(char str[]) {
    int tmp, i, j;
    for (i = 0, j = str_len(str)-1; i < j; ++i, --j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

int str_len(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}