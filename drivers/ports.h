#include "../cpu/types.h"

unsigned char read_bytes_from_port(uint16_t port);
void write_bytes_to_port(uint16_t port, uint8_t data);
unsigned short read_word_from_port(uint16_t port);
void write_word_to_port(uint16_t port, uint16_t data);
