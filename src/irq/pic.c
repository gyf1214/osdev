#include "irq/pic.h"
#include "io/port.h"

void initPIC() {
    outb(PIC1Data, 0xff);
    outb(PIC2Data, 0xff);

    outb(PIC1Command, PICICW1);
    outb(PIC1Data, PIC1ICW2);
    outb(PIC1Data, PIC1ICW3);
    outb(PIC1Data, PICICW4);

    outb(PIC2Command, PICICW1);
    outb(PIC2Data, PIC2ICW2);
    outb(PIC2Data, PIC2ICW3);
    outb(PIC2Data, PICICW4);

    outb(PIC1Data, PIC1IMR);
    outb(PIC2Data, PIC2IMR);
}

void picEOI(uint8_t irq) {
    if (irq >= 8) outb(PIC2Command, PICEOI);
    outb(PIC1Command, PICEOI);
}

void picSetMask(uint8_t irq, int mask) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1Data;
    } else {
        port = PIC2Data;
        irq -= 8;
    }

    value = inb(port);
    if (mask) {
        value |= (1 << irq);
    } else {
        value &= (~(1 << irq));
    }
    outb(port, value);
}
