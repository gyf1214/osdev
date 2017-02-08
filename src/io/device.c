#include "io/device.h"
#include "mm/kmem.h"
#include "io/serial.h"
#include "io/framebuffer.h"

void initDevice() {
    kmemInitCache(KmemDevice, sizeof(device_t), kmemDefaultCtor);

    initSerial();
    initFB();
}

ssize_t deviceWrite(device_t *dev, const char *data, size_t n) {
    if (dev -> write) {
        return dev -> write(dev -> info, data, n);
    } else {
        return -1;
    }
}

ssize_t deviceRead(device_t *dev, char *buf, size_t n) {
    if (dev -> read) {
        return dev -> read(dev -> info, buf, n);
    } else {
        return -1;
    }
}

void deviceControl(device_t *dev, uint32_t flag, uint32_t data) {
    if (dev -> control) {
        dev -> control(dev -> info, flag, data);
    }
}
