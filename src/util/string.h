#ifndef __STRING
#define __STRING

#include "util/type.h"

int strlen(const char *str);
char *strncpy(char *dst, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
void *memset(void *ptr, int ch, size_t size);
void *memcpy(void *dst, const void *src, size_t size);

#endif
