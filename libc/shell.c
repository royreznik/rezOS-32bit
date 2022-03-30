#include "../drivers/screen.h"
#include "string.h"

void run_command(char *input) {

    if (str_cmp(input, "WTF") == 0) {
        kprint("WTF did you except it to do?\n");
    } else {
        kprint("Invalid command");
    }
    kprint("> ");
}