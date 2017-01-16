#include "io/device.h"
#include "io/serial.h"
#include "io/framebuffer.h"

device_t deviceCOM1, deviceFB;

void initDevice() {
    //init serial port COM1
    initSerial(SerialCOM1);
    deviceCOM1.info = SerialCOM1;
    deviceCOM1.read = NULL;
    deviceCOM1.write = serialWrite;
    deviceCOM1.control = NULL;

    //init framebuffer
    fbClear();
    deviceFB.info = 0;
    deviceFB.read = NULL;
    deviceFB.write = fbWrite;
    deviceFB.control = NULL;
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
