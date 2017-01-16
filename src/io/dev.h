#ifndef __DEV
#define __DEV

#include "util/type.h"

typedef void (*write_t)(uint32_t, const char *, size_t);
typedef size_t (*read_t)(uint32_t, char *, size_t);

typedef struct {
    uint32_t info;
    read_t read;
    write_t write;
}dev_t;

void initDev(void);
void devWrite(dev_t *dev, const char *data, size_t n);
size_t devRead(dev_t *dev, char *buf, size_t n);

extern dev_t devCOM1;

#endif
