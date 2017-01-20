#ifndef __DEVICE
#define __DEVICE

#include "util/type.h"

typedef void (*write_t)(uint32_t, const char *, size_t);
typedef size_t (*read_t)(uint32_t, char *, size_t);
typedef void (*control_t)(uint32_t, uint32_t);

typedef struct device {
    uint32_t info;
    read_t read;
    write_t write;
    control_t control;
}device_t;

void initDevice(void);
void deviceWrite(device_t *dev, const char *data, size_t n);
size_t deviceRead(device_t *dev, char *buf, size_t n);
void deviceControl(device_t *dev, uint32_t sig);

#endif
