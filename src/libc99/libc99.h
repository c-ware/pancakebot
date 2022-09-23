#ifndef CWARE_LIBC99_H
#define CWARE_LIBC99_H

#define libc99_count_digits(n, base, location, type) \
    0;                                               \
                                                     \
    do {                                             \
        type __C99_COUNT_DIGITS_N = (n);             \
                                                     \
        if(__C99_COUNT_DIGITS_N == 0) {              \
            (location) = 1;                          \
            break;                                   \
        }                                            \
                                                     \
        while(__C99_COUNT_DIGITS_N  >= 1) {          \
            (location)++;                            \
            __C99_COUNT_DIGITS_N  /= (base);         \
        }                                            \
    } while(0)

#define libc99_pow(base, exponent, location, type)                            \
    0;                                                                        \
                                                                              \
    do {                                                                      \
        int __C99_POW_INDEX = 0;                                              \
        type __C99_POW_BASE = (base);                                         \
        type __C99_POW_TOTAL = 0;                                             \
                                                                              \
        if(__C99_POW_BASE < 0)                                                \
            __C99_POW_BASE = __C99_POW_BASE * -1;                             \
                                                                              \
        __C99_POW_TOTAL = __C99_POW_BASE;                                     \
                                                                              \
        if((exponent) == 0) {                                                 \
            (location) = 1;                                                   \
            break;                                                            \
        }                                                                     \
                                                                              \
        for(__C99_POW_INDEX = 1; __C99_POW_INDEX < (exponent);                \
                                                         __C99_POW_INDEX++) { \
            __C99_POW_TOTAL *= __C99_POW_BASE;                                \
        }                                                                     \
                                                                              \
        (location) = __C99_POW_TOTAL;                                         \
    } while(0)

/*
 * C89 compliant semi-implementation of the vsnprintf function from C99.
 *
 * @param buffer: the buffer to write to
 * @param length: the maximum length of the buffer
 * @param specifiers: the va_list containing the arguments
*/
size_t libc99_vsnprintf(char *buffer, size_t length, const char *format,
                    va_list specifiers);

/*
 * C89 compliant semi-implementation of the snprintf function from C99.
 *
 * @param buffer: the buffer to write to
 * @param length: the maximum length of the buffer
 * @param format: the format string
*/
size_t libc99_snprintf(char *buffer, size_t length, const char *format, ...);

/*
 * C89 compliant semi-implementation of the common extenstion to the C
 * standard library to convert an integer to a string.
 *
 * @param n: the number to convert
 * @param buffer: the buffer to write to
 * @param length: the maximum length of the buffer
 * @param base: the base the number is represented as
 * @return: number of bytes written excluding the NUL byte
*/
int libc99_itoa(int n, char *buffer, int length, int base);

#endif
