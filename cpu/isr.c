#include "isr.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"


isr_t interrupt_handlers[IDT_ENTRIES];

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


void initialize_isr() {
    idt_reg.limit = IDT_ENTRIES * sizeof(idt) - 1;
    idt_reg.base = (uint32_t) &idt;
    set_idt_gate(0, isr0, 0x08, 0x8E);
    set_idt_gate(1, isr1, 0x08, 0x8E);
    set_idt_gate(2, isr2, 0x08, 0x8E);
    set_idt_gate(3, isr3, 0x08, 0x8E);
    set_idt_gate(4, isr4, 0x08, 0x8E);
    set_idt_gate(5, isr5, 0x08, 0x8E);
    set_idt_gate(6, isr6, 0x08, 0x8E);
    set_idt_gate(7, isr7, 0x08, 0x8E);
    set_idt_gate(8, isr8, 0x08, 0x8E);
    set_idt_gate(9, isr9, 0x08, 0x8E);
    set_idt_gate(10, isr10, 0x08, 0x8E);
    set_idt_gate(11, isr11, 0x08, 0x8E);
    set_idt_gate(12, isr12, 0x08, 0x8E);
    set_idt_gate(13, isr13, 0x08, 0x8E);
    set_idt_gate(14, isr14, 0x08, 0x8E);
    set_idt_gate(15, isr15, 0x08, 0x8E);
    set_idt_gate(16, isr16, 0x08, 0x8E);
    set_idt_gate(17, isr17, 0x08, 0x8E);
    set_idt_gate(18, isr18, 0x08, 0x8E);
    set_idt_gate(19, isr19, 0x08, 0x8E);
    set_idt_gate(20, isr20, 0x08, 0x8E);
    set_idt_gate(21, isr21, 0x08, 0x8E);
    set_idt_gate(22, isr22, 0x08, 0x8E);
    set_idt_gate(23, isr23, 0x08, 0x8E);
    set_idt_gate(24, isr24, 0x08, 0x8E);
    set_idt_gate(25, isr25, 0x08, 0x8E);
    set_idt_gate(26, isr26, 0x08, 0x8E);
    set_idt_gate(27, isr27, 0x08, 0x8E);
    set_idt_gate(28, isr28, 0x08, 0x8E);
    set_idt_gate(29, isr29, 0x08, 0x8E);
    set_idt_gate(30, isr30, 0x08, 0x8E);
    set_idt_gate(31, isr31, 0x08, 0x8E);


    /* All devices that are interrupt capable have a line connecting to the PIC, which is the only device
     * that connected directly to the CPU.
     *
     * IRQ are interrupt requests made by those devices, and we need to handle them too, but there is a problem.
     * the PIC default interrupt number are 0x8-0xF and 0x70-0x77, which conflict with our cpu interrupts, so we
     * need to change it, that called Remap the PIC.
     *
     * the PIC can be communicated with I/O bus, each have a command port and data port.
     *
     * Master: command: 0x20, data: 0x21
     * slave: command: 0xA0, data: 0xA1
     */

    write_bytes_to_port(0x20, 0x11); // Reset PIC master
    write_bytes_to_port(0xA0, 0x11); // Reset PIC slave
    write_bytes_to_port(0x21, 0x20); // start Master at 32
    write_bytes_to_port(0xA1, 0x28); // start Slave at 40
    write_bytes_to_port(0x21, 0x04); // setup cascading
    write_bytes_to_port(0xA1, 0x02);
    write_bytes_to_port(0x21, 0x01);
    write_bytes_to_port(0xA1, 0x01);
    write_bytes_to_port(0x21, 0x0);  // Done
    write_bytes_to_port(0xA1, 0x0);  // Done


    set_idt_gate(32, irq0, 0x08, 0x8E);
    set_idt_gate(33, irq1, 0x08, 0x8E);
    set_idt_gate(34, irq2, 0x08, 0x8E);
    set_idt_gate(35, irq3, 0x08, 0x8E);
    set_idt_gate(36, irq4, 0x08, 0x8E);
    set_idt_gate(37, irq5, 0x08, 0x8E);
    set_idt_gate(38, irq6, 0x08, 0x8E);
    set_idt_gate(39, irq7, 0x08, 0x8E);
    set_idt_gate(40, irq8, 0x08, 0x8E);
    set_idt_gate(41, irq9, 0x08, 0x8E);
    set_idt_gate(42, irq10, 0x08, 0x8E);
    set_idt_gate(43, irq11, 0x08, 0x8E);
    set_idt_gate(44, irq12, 0x08, 0x8E);
    set_idt_gate(45, irq13, 0x08, 0x8E);
    set_idt_gate(46, irq14, 0x08, 0x8E);
    set_idt_gate(47, irq15, 0x08, 0x8E);

    initialize_idt();
}

void isr_handler(registers_t r) {
    kprint("\nReceived interrupt!:");
    char s[3];
    i_to_a(r.interrupt, s);
    kprint(s);
}


void set_interrupt_handler(uint8_t interrupt, isr_t handler) {
    interrupt_handlers[interrupt] = handler;
}


void irq_handler(registers_t r) {
    if(r.interrupt >= 40) {
        write_bytes_to_port(0xA0, 0x20);
    }
    write_bytes_to_port(0x20, 0x20);

    isr_t handler = interrupt_handlers[r.interrupt];

    if (handler != 0) {
        handler(r);
    }
}