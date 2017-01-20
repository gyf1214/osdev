#include "util/log.h"
#include "util/string.h"

static device_t *logger = NULL;

void klogSetDevice(device_t *device) {
    logger = device;
}

void klog(const char *line) {
    if (!logger) return;
    int len = strlen(line);
    deviceWrite(logger, line, len);
    deviceWrite(logger, "\n", 1);
}
