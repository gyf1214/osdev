#ifndef __SERIAL
#define __SERIAL

#include "util/type.h"

#define SerialCOM1      0x3fb

#define SerialData(x)   (x)
#define SerialIntr(x)   ((x) + 1)
#define SerialFIFO(x)   ((x) + 2)
#define SerialLine(x)   ((x) + 3)
#define SerialModem(x)  ((x) + 4)
#define SerialStatus(x) ((x) + 5)

#define SerialDLAB      0x80
#define SerialBaud      3
#define SerialIntrSet   0x0
#define SerialFIFOSet   0xc7
#define SerialLineSet   0x3
#define SerialModemSet  0xb

void initSerial(uint16_t port);
int serialReceived(uint16_t port);
char serialGetChar(uint16_t port);
int serialReady(uint16_t port);
void serialPutChar(uint16_t port, char ch);

#endif
