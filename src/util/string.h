#ifndef __STRING
#define __STRING

#include "util/type.h"

int strlen(const char *str);
void *memset(void *ptr, int ch, size_t size);
void *memcpy(void *dst, const void *src, size_t size);

#endif
