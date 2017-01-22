#include "string.h"

int strlen(const char *str) {
    int n = 0;
    while (*str++) ++n;
    return n;
}

void *memset(void *ptr, int ch, size_t size) {
    uint8_t *a = (uint8_t *)ptr;
    uint8_t x = (uint8_t)ch;
    while (--size > 0) {
        *a++ = x;
    }
    return ptr;
}

void memcpy(void *restrict dst, const void *restrict src, size_t size) {
    char *restrict d = (char *)dst;
    const char *restrict s = (const char *)src;

    while (size-- > 0) {
        *d++ = *s++;
    }
}
