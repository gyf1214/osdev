#ifndef __DEVICE
#define __DEVICE

#include "util/type.h"

typedef struct device {
    uint32_t info;
    ssize_t (*read)(uint32_t info, void *buf, size_t size);
    ssize_t (*write)(uint32_t info, const void *buf, size_t size);
    int (*control)(uint32_t info, uint32_t flag, uint32_t data);
}device_t;

void initDevice(void);
void deviceWrite(device_t *dev, const char *data, size_t n);
size_t deviceRead(device_t *dev, char *buf, size_t n);
void deviceControl(device_t *dev, uint32_t flag, uint32_t data);

#endif
