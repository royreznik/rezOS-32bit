#include "idt.h"
#include "bitwise.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int interrupt, void *handler, uint16_t segment_descriptor, uint8_t flags) {
    int handler_address = (uint32_t) handler;
    idt[interrupt].low_offset = handler_address & 0xFFFF;
    idt[interrupt].segment_selector = segment_descriptor;
    idt[interrupt].reserved = 0;
    idt[interrupt].flags = flags;
    idt[interrupt].high_offset = (handler_address >> 16) & 0xFFFF;
}

void enable_idt_gate(int interrupt) {
    FLAG_SET(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void disable_idt_gate(int interrupt) {
    FLAG_UNSET(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void initialize_idt() {
    // Using __volatile__ makes the compiler not optimize this asm line, avoid cache and ext.
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}