#include "string.h"

int strlen(const char *str) {
    int n = 0;
    while (*str++) ++n;
    return n;
}

char *strncpy(char *dst, const char *src, size_t n) {
    char *ret = dst;
    while (*src && --n > 0) {
        *dst++ = *src++;
    }
    *dst = 0;
    return ret;
}

int strcmp(const char *s1, const char *s2) {
    for (; *s1 && *s2 && *s1 == *s2; ++s1, ++s2);
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void *memset(void *ptr, int ch, size_t size) {
    uint8_t *a = ptr;
    uint8_t x = (uint8_t)ch;
    while (size-- > 0) {
        *a++ = x;
    }
    return ptr;
}

void *memcpy(void *dst, const void *src, size_t size) {
    char *d = dst;
    const char *s = src;

    while (size-- > 0) {
        *d++ = *s++;
    }
    return dst;
}
