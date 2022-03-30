#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void mem_copy(int8_t *source, int8_t *dest, int nbytes);
void mem_set(uint8_t *dest, uint8_t val, uint32_t len);
#endif