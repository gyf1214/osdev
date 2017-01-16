#include "io/dev.h"
#include "io/serial.h"
#include "io/framebuffer.h"

dev_t devCOM1, devFramebuffer;

void initDev() {
    //init serial port COM1
    initSerial(SerialCOM1);
    devCOM1.info = SerialCOM1;
    devCOM1.read = NULL;
    devCOM1.write = serialWrite;
    devCOM1.control = NULL;

    //init framebuffer
    fbClear();
    devFramebuffer.info = 0;
    devFramebuffer.read = NULL;
    devFramebuffer.write = fbWrite;
    devFramebuffer.control = NULL;
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

void devControl(dev_t *dev, uint32_t sig) {
    if (dev -> control) {
        dev -> control(dev -> info, sig);
    }
}
