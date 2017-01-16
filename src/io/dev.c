#include "io/dev.h"
#include "io/serial.h"

dev_t devCOM1;

void initDev() {
    initSerial(SerialCOM1);
    devCOM1.info = SerialCOM1;
    devCOM1.read = NULL;
    devCOM1.write = serialWrite;
}

void devWrite(dev_t *dev, const char *data, size_t n) {
    if (dev -> write) {
        dev -> write(dev -> info, data, n);
    }
}

size_t devRead(dev_t *dev, char *buf, size_t n) {
    if (dev -> read) {
        return dev -> read(dev -> info, buf, n);
    } else {
        return 0;
    }
}
