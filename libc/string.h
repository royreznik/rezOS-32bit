#ifndef STRING_H
#define STRING_H

#include "../cpu/types.h"

void i_to_a(int n, char str[]);
void str_rev(char str[]);
int str_len(char str[]);
void append(char str[], char c);
void backspace(char str[]);
int str_cmp(char str1[], char str2[]);

#endif