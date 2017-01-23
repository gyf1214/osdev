#ifndef __PIC
#define __PIC

#include "util/type.h"

#define PIC1            0x20
#define PIC2            0xa0
#define PIC1Command     PIC1
#define PIC1Data        (PIC1 + 1)
#define PIC2Command     PIC2
#define PIC2Data        (PIC2 + 1)

#define PICICW1ICW4     0x01
#define PICICW1Single   0x02
#define PICICW1Level    0x08
#define PICICW1Init     0x10

#define PIC1Offset      0x20
#define PIC2Offset      0x40

#define PIC2IRQ         2

#define PICICW1         (PICICW1ICW4 | PICICW1Init)
#define PIC1ICW2        PIC1Offset
#define PIC2ICW2        PIC2Offset
#define PIC1ICW3        (1 << PIC2IRQ)
#define PIC2ICW3        PIC2IRQ
#define PICICW4         0x01

#define PIC1IMR         0xfb
#define PIC2IMR         0xff

#define PICEOI          0x20

void initPIC(void);
void picEOI(uint8_t irq);
void picSetMask(uint8_t irq, int mask);

#endif
