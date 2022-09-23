/*
 * Functions from the C standard library.
*/

#include <stdio.h>

#include "libc99.h"

int libc99_itoa(int n, char *buffer, int length, int base) {
    int cursor = 0;
    int place = 0;
    int digits = 0;

    if(n < 0 && length >= 1) {
        buffer[0] = '-';
        n = n * -1;
        cursor++;
    }

    digits = libc99_count_digits(n, base, digits, int);
    place = libc99_pow(base, digits - 1, place, int);

    while(place >= 1 && cursor < length) {
        buffer[cursor] = "0123456789ABCDEF"[(n / place) % base];
        cursor++;
        place /= base;
    }

    buffer[cursor] = '\0';

    return cursor;
}
