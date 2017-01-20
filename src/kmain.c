#include "mm/segment.h"
#include "mm/kmem.h"
#include "io/device.h"
#include "io/pci.h"
#include "io/serial.h"
#include "io/framebuffer.h"
#include "irq/interrupt.h"
#include "util/string.h"
#include "util/multiboot.h"
#include "util/log.h"

int kmain(multiboot_info_t *mbi) {
    initSegment();
    initInterrupt();
    initKmem();
    initDevice();
    initPCI();

    device_t *com1 = initSerial(SerialCOM1);
    device_t *fb = initFB();
    klogSetDevice(com1);

    klog("log start");

    char *str = "hello world!\n";
    int len = strlen(str);
    deviceWrite(fb, str, len);

    mbi = mbi;

    __asm__("int3\n");

    return 0;
}
