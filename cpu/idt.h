#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CS 0x08

typedef enum {
    IDT_FLAG_GATE_TASK          = 0x05,
    IDT_FLAG_GATE_16BIT_INT     = 0x06,
    IDT_FLAG_GATE_16BIT_TRAP    = 0x07,
    IDT_FLAG_GATE_32BIT_INT     = 0x0E,
    IDT_FLAG_GATE_32BIT_TRAP    = 0x0F,

    IDT_FLAG_RING0              = (0 << 5),
    IDT_FLAG_RING1              = (1 << 5),
    IDT_FLAG_RING2              = (2 << 5),
    IDT_FLAG_RING3              = (3 << 5),

    IDT_FLAG_PRESENT            = 0x80
} IDT_FLAGS;

// How every interrupt gate (handler) is defined
/* Interrupt descriptor:
 * 63                   48|47|46 45| 44|43   40|39         32
 * +-----------------------------------------------------+
 * | high offset(31:16)  | P | DPL | 0 | Type | Reserved |
 * +-----------------------------------------------------+
 * |   segment selector  |         low offset(15:00)     |
 * +-----------------------------------------------------+
 * 31                  16|15                             0
 *
 */
typedef struct {
    uint16_t low_offset; // Lower 16 bits of handler function address
    uint16_t segment_selector; // Entry in the gdt, Going to be the code segment
    uint8_t reserved; // This byte currently not in use, so it will always be zero.
    uint8_t flags; /* flags for the idt gate.
                    * Type - 4 bits (0-3): Type of the idt gate, (like 16 or 32 bit and ext.)
                    * 0 - 1 bit (4): set to 0 for interrupt gate
                    * DPL - 2 bits (5-6): Privilege level of caller (0=kernel, 3=user)
                    * P - 1 bit (7): is the interrupt is present (must be 1 to be valid)
                    */
    uint16_t high_offset; // High 16 bits of the handler function address
} __attribute__((packed)) idt_gate_t;


typedef struct {
    uint16_t limit;  // How much address will be the idt
    uint32_t base;  // the first gate in the idt
} __attribute__((packed)) idt_register_t; // Also, can be called idt descriptor


#define IDT_ENTRIES 256
extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;


void set_idt_gate(int interrupt, uint32_t base, uint16_t segment_descriptor, uint8_t flags);

void enable_idt_gate(int interrupt);

void disable_idt_gate(int interrupt);

void initialize_idt();

#endif
