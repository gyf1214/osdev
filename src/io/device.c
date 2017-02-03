#include "io/device.h"
#include "mm/kmem.h"
#include "io/serial.h"
#include "io/framebuffer.h"

void initDevice() {
    kmemInitCache(KmemDevice, sizeof(device_t), kmemDefaultCtor);
}

void deviceWrite(device_t *dev, const char *data, size_t n) {
    if (dev -> write) {
        dev -> write(dev -> info, data, n);
    }
}

size_t deviceRead(device_t *dev, char *buf, size_t n) {
    if (dev -> read) {
        return dev -> read(dev -> info, buf, n);
    } else {
        return 0;
    }
}

void deviceControl(device_t *dev, uint32_t sig) {
    if (dev -> control) {
        dev -> control(dev -> info, sig);
    }
}
