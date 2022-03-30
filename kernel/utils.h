#ifndef UTIL_H
#define UTIL_H

#include "../cpu/types.h"

void i_to_a(int n, char str[]);
void mem_copy(int8_t *source, int8_t *dest, int nbytes);
void mem_set(uint8_t *dest, uint8_t val, uint32_t len);
void str_rev(char str[]);
int strlen(char str[]);
#endif