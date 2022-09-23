/*
 * Implementations of snprintf and vsnprintf. Not all things are
 * included, like padding, but quite a few things are.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "libc99.h"

#define libc99_snprintf_num(type, base, symbols)                        \
do {                                                                    \
    int place = 0;                                                      \
    int digits = 0;                                                     \
    type C99_NUM = va_arg(specifiers, type);                            \
                                                                        \
    if(C99_NUM < 0 && length >= 1) {                                    \
        buffer[(*(cursor))] = '-';                                      \
        C99_NUM = C99_NUM * -1;                                         \
        (*cursor)++;                                                    \
    }                                                                   \
                                                                        \
    digits = libc99_count_digits(C99_NUM, base, digits, type);          \
    place = libc99_pow(base, digits - 1, place, type);                  \
                                                                        \
    while(place >= 1 && (*cursor) < length) {                           \
        buffer[*cursor] = symbols[(C99_NUM / place) % base];            \
        (*cursor)++;                                                    \
        place /= base;                                                  \
    }                                                                   \
                                                                        \
    buffer[(*cursor)] = '\0';                                           \
} while(0)

void libc99_snprintf_string(char *buffer, size_t length, int *cursor,
                        va_list specifiers) {
    int index = 0;
    char *string = va_arg(specifiers, char*);

    for(index = 0; string[index] != '\0' && (*cursor) < length; index++) {
        buffer[*cursor] = string[index];
        (*cursor)++;
    }
}

void libc99_snprintf_ptr(char *buffer, size_t length, int *cursor,
                        va_list specifiers) {
    void *ptr = va_arg(specifiers, void*);
    unsigned long integer_ptr = (unsigned long) ptr;
}

int libc99_snprintf_write(char *buffer, size_t length, int *cursor, int char_a,
                       int char_b, va_list specifiers) {
    switch(char_a) {
        case 's': /* Strings */
            libc99_snprintf_string(buffer, length, cursor, specifiers);
            break;

        case 'i': /* Integer */
            libc99_snprintf_num(int, 10, "0123456789");
            break;

        case 'u': /* Unsigned integer */
            libc99_snprintf_num(unsigned int, 10, "0123456789");
            break;

        case 'l': /* Long */
            switch(char_b) {
                case 'u': /* Unsigned long */
                    libc99_snprintf_num(unsigned long, 10, "0123456789");
                    break;

                case 'i': /* Signed long */
                    libc99_snprintf_num(long, 10, "0123456789");
                    break;
            }
            
            return 1;
        case 'x': /* Lowercase hexadecimal; unsigned int */
            libc99_snprintf_num(unsigned int, 16, "0123456789abcdef");
            break;

        case 'X': /* Uppercase hexadecimal; unsigned int */
            libc99_snprintf_num(unsigned int, 16, "0123456789ABCDEF");
            break;

        case '%': /* Escaped percent */
            buffer[(*cursor)] = '%';
            (*cursor)++;

            break;
    }

    return 0;
}

size_t libc99_snprintf(char *buffer, size_t length, const char *format, ...) {
    size_t written = 0;
    va_list specifiers;

    va_start(specifiers, format);
    written = libc99_vsnprintf(buffer, length, format, specifiers);     
    va_end(specifiers);

    return written;
}

size_t libc99_vsnprintf(char *buffer, size_t length, const char *format,
                    va_list specifiers) {
    int buffer_cursor = 0;
    int format_cursor = 0;
    int escaped = 0;
    size_t written = 0;

    for(format_cursor = 0; format[format_cursor] != '\0' &&
                                     buffer_cursor < length; format_cursor++) {
        char character_a = format[format_cursor];
        char character_b = -1;

        if(format[format_cursor + 1] != '\0')
            character_b = format[format_cursor + 1];

        /* Do formatting */
        if(escaped == 1) {
            format_cursor += libc99_snprintf_write(buffer, length,
                                                  &buffer_cursor, character_a,
                                                  character_b, specifiers);
            escaped = 0;

            continue;
        }

        /* Get ready for an escape */
        if(character_a == '%') {
            escaped = 1;

            continue;
        }

        escaped = 0;
        buffer[buffer_cursor] = character_a;
        buffer_cursor++;
    }

    buffer[buffer_cursor] = '\0';

    return written;
}
