#include "string.h"

void i_to_a(int n, char str[]) {
    int i = 0;
    int sign = (n < 0);
    if (sign) {
        n = -n;
    }
    do {
        str[i++] = n % 10 + '0';
    } while((n /= 10) > 0);

    if (sign) {
        str[i++] = '-';
    }
    str[i] = '\0';
    str_rev(str);
}

void str_rev(char str[]) {
    int tmp, i, j;
    for (i = 0, j = str_len(str)-1; i < j; ++i, --j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

int str_len(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}


void append(char str[], char c) {
    int len = str_len(str);
    str[len] = c;
    str[len+1] = '\0';
}

void backspace(char str[]) {
    int len = str_len(str);
    str[len-1] = '\0';
}

int str_cmp(char str1[], char str2[]) {
    int i;
    for(i = 0; str1[i] == str2[i]; ++i) {
        if (str1[i] == '\0') {
            return 0;
        }
    }
    return str1[i] - str2[i];
}