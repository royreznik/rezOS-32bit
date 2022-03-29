#ifndef ISR_H
#define ISR_H

#include "types.h"
#include "idt.h"

typedef struct {
    uint32_t ds; // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
    uint32_t interrupt, err_code; // interrupt number and error code if needed
    uint32_t eip, cs, eflags, useresp, ss; // pushed by the processor automaticlly
} registers_t;

void initialize_isr();
void isr_handler(registers_t r);

typedef void (*isr_t)(registers_t);
void set_interrupt_handler(uint8_t interrupt, isr_t handler);

#endif
