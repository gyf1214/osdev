#ifndef __LOG
#define __LOG

#include "io/device.h"

void klogSetDevice(device_t *dev);
void klog(const char *line);

#endif
