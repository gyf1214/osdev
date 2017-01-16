#include "io/serial.h"
#include "io/port.h"

void initSerial(uint16_t port) {
    outb(SerialIntr(port), SerialIntrSet);
    outb(SerialLine(port), SerialDLAB);
    outb(SerialData(port), SerialBaud & 0xff);
    outb(SerialIntr(port), SerialBaud >> 8);
    outb(SerialFIFO(port), SerialFIFOSet);
    outb(SerialLine(port), SerialLineSet);
    outb(SerialModem(port), SerialModemSet);
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

void serialWrite(uint32_t port, const char *data, size_t n) {
    while (--n > 0) {
        serialPutChar(port, *data++);
    }
}
