#include "../drivers/screen.h"
#include "string.h"

void run_command(char *input) {

    if (str_cmp(input, "WTF") == 0) {
        kprint("WTF did you except it to do?\n");
    } else if (str_len(input) == 0) {

    } else {
        kprint("Invalid command\n");
    }
    kprint("> ");
}