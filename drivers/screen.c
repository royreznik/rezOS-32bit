#include "screen.h"
#include "ports.h"
#include "../libc/mem.h"

#define CALC_OFFSET(col, row) (2 * (row * MAX_COLS + col))
#define CALC_OFFSET_ROW(offset) (offset / (2 * MAX_COLS))
#define CALC_OFFSET_COL(offset) ((offset - (CALC_OFFSET_ROW(offset)*2*MAX_COLS))/2)

#define BACKSPACE 0x08

int get_cursor_offset();

void set_cursor_offset(int offset);

int putc(char c, int col, int row, char attr);

int kprint_at(char *message, int col, int row, char attr) {
    int offset;
    int i = 0;

    while (message[i] != 0) {
        offset = putc(message[i++], col, row, attr);
        col = CALC_OFFSET_COL(offset);
        row = CALC_OFFSET_ROW(offset);
    }
    return i;
}

int kprint(char *message) {
    return kprint_at(message, -1, -1, WHITE_ON_BLACK);
}

int kprint_color(char *message, char attr) {
    return kprint_at(message, -1, -1, attr);
}

int kprint_backspace() {
    int offset = get_cursor_offset() - 2;
    int row = CALC_OFFSET_ROW(offset);
    int col = CALC_OFFSET_COL(offset);
    return putc(BACKSPACE, col, row, WHITE_ON_BLACK);
}


/**
 * print a character to the screen
 *
 * @param c what charcter to print to the screen
 * @param col which col
 * @param row  which row
 * @param attr which attribute (color)
 * @return
 */
int putc(char c, int col, int row, char attr) {
    uint8_t *vidmem = (uint8_t *) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2 * (MAX_COLS) * (MAX_ROWS) - 2] = 'E';
        vidmem[2 * (MAX_COLS) * (MAX_ROWS) - 1] = RED_ON_WHITE;
        return CALC_OFFSET(col, row);
    }

    int offset = (col >= 0 && row >= 0) ? CALC_OFFSET(col, row) : get_cursor_offset();

    if (c == '\n') {
        row = CALC_OFFSET_ROW(offset) + 1;
        offset = CALC_OFFSET(0, row);
    } else if (c == BACKSPACE) {
        vidmem[offset] = ' ';
        vidmem[offset + 1] = attr;
    } else {
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
        offset += 2;
    }

    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        for (int i = 1; i < MAX_ROWS; ++i) {
            int dest_line = i - 1;
            mem_copy((int8_t*)(CALC_OFFSET(0, i) + vidmem),
                     (int8_t*)(CALC_OFFSET(0, dest_line) + vidmem),
                     MAX_COLS * 2);
        }

        int last_row = MAX_ROWS - 1;
        uint8_t* last_line = CALC_OFFSET(0, last_row) + (uint8_t*)VIDEO_ADDRESS;
        for (int i = 0; i < MAX_COLS * 2; ++i) {
            last_line[i] = 0;
        }

        offset -= (2 * MAX_COLS);
    }
    set_cursor_offset(offset);
    return offset;
}


void clear_screen() {
    uint16_t screen_size = MAX_COLS * MAX_ROWS;
    uint8_t *screen = (uint8_t *) VIDEO_ADDRESS;

    for (int i = 0; i < screen_size; ++i) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(CALC_OFFSET(0,0));
}


/**
 * Use the vga ports to get the current cursor position
 * 1. Ask for the high bytes of the curser (data 14)
 * 2. Ask for the low bytes (data 15)
 * @return th offset of the curser
 */
int get_cursor_offset() {
    write_bytes_to_port(REG_SCREEN_CTRL, 14);
    int offset = read_bytes_from_port(REG_SCREEN_DATA) << 8;
    write_bytes_to_port(REG_SCREEN_CTRL, 15);
    offset += read_bytes_from_port(REG_SCREEN_DATA);
    return offset * 2; // Position * size of character cell
}

/**
 * Same as get_cursor_offest but for writing the offset
 * @param offset
 */
void set_cursor_offset(int offset) {
    offset /= 2;
    write_bytes_to_port(REG_SCREEN_CTRL, 14);
    write_bytes_to_port(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
    write_bytes_to_port(REG_SCREEN_CTRL, 15);
    write_bytes_to_port(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

