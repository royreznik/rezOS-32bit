#include "idt.h"
#include "bitwise.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int interrupt, uint32_t handler, uint16_t segment_descriptor, uint8_t flags) {
    idt[interrupt].low_offset = handler & 0xFFFF;
    idt[interrupt].segment_selector = segment_descriptor;
    idt[interrupt].reserved = 0;
    idt[interrupt].flags = flags;
    idt[interrupt].high_offset = (handler >> 16) & 0xFFFF;
}

void enable_idt_gate(int interrupt) {
    FLAG_SET(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void disable_idt_gate(int interrupt) {
    FLAG_UNSET(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void initialize_idt() {
    // Using __volatile__ makes the compiler not optimize this asm line, avoid cache and ext.
    idt_reg.limit = (uint16_t)IDT_ENTRIES * ((uint8_t )(sizeof(idt) - 1));
    idt_reg.base = (uint32_t) &idt;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}