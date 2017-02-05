#include "io/serial.h"
#include "io/port.h"
#include "mm/kmem.h"

device_t *initSerial(uint16_t port) {
    outb(SerialIntr(port), SerialIntrSet);
    outb(SerialLine(port), SerialDLAB);
    outb(SerialData(port), SerialBaud & 0xff);
    outb(SerialIntr(port), SerialBaud >> 8);
    outb(SerialFIFO(port), SerialFIFOSet);
    outb(SerialLine(port), SerialLineSet);
    outb(SerialModem(port), SerialModemSet);

    device_t *ret = (device_t *)kalloc(KmemDevice);
    ret -> info = port;
    ret -> write = serialWrite;
    return ret;
}

int serialReceived(uint16_t port) {
    return inb(SerialStatus(port)) & 1;
}

char serialGetChar(uint16_t port) {
    while (!serialReceived(port));
    return inb(SerialData(port));
}

int serialReady(uint16_t port) {
    return inb(SerialStatus(port)) & 0x20;
}

void serialPutChar(uint16_t port, char ch) {
    while (!serialReady(port));
    outb(SerialData(port), ch);
}

ssize_t serialWrite(uint32_t port, const void *data, size_t n) {
    ssize_t ret = n;
    const char *buf = data;
    while (n-- > 0) {
        serialPutChar(port, *buf++);
    }
    return ret;
}
