#include "mm/segment.h"
#include "io/serial.h"

int kmain() {
    initSegment();
    initSerial(SerialCOM1);
    serialPutChar(SerialCOM1, 'H');

    return 0;
}
