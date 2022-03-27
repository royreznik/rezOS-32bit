#include "ports.h"
/**
 * IN opcode - input from port (reading from port)
 * OUT - output to port (writing to port)
 */


/**
 * Read byte from specific port
 * @param port address to the port
 * @return the output
 */
unsigned char read_bytes_from_port(uint16_t port) {
    unsigned char result;
    /*
     * "=a" means to set the value of result to be the value of eax
     * "d" means to put the value of port in edx
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void write_bytes_to_port(uint16_t port, uint8_t data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short read_word_from_port(uint16_t port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void write_word_to_port(uint16_t port, uint16_t data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}