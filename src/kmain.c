#include "mm/segment.h"
#include "mm/kmem.h"
#include "io/device.h"
#include "io/serial.h"
#include "io/framebuffer.h"
#include "irq/interrupt.h"
#include "util/string.h"
#include "util/multiboot.h"

int kmain(multiboot_info_t *mbi) {
    initSegment();
    initInterrupt();
    initKmem();
    initDevice();
    device_t *com1 = initSerial(SerialCOM1);
    device_t *fb = initFB();

    char *str = "hello world!\n";
    int len = strlen(str);
    deviceWrite(com1, str, len);
    deviceWrite(fb, str, len);

    mbi = mbi;

    __asm__("int $0;");

    return 0;
}
