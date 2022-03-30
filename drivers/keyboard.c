#include "keyboard.h"
#include "../cpu/isr.h"
#include "ports.h"
#include "screen.h"
#include "../libc/function.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../libc/shell.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char console_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                          "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                          "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                          "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                          "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                          "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
                          '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                          'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                          'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                          'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_interrupt_handler(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = read_bytes_from_port(KEYBOARD_PIC_PORT);

    if (scancode > SC_MAX) {
        return;
    } else if (scancode == BACKSPACE) {
        backspace(console_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        run_command(console_buffer);
        console_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(console_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
    set_interrupt_handler(KEYBOARD_INTERRUPT, keyboard_interrupt_handler);
}