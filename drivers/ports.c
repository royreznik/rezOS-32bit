/**
 * IN opcode - input from port (reading from port)
 * OUT - output to port (writing to port)
 */


/**
 * Read byte from specific port
 * @param port address to the port
 * @return the output
 */
unsigned char read_bytes_from_port(unsigned short port) {
    unsigned char result;
    /*
     * "=a" means to set the value of result to be the value of eax
     * "d" means to put the value of port in edx
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void write_bytes_to_port(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short read_word_from_port(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void write_word_to_port(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}