#include "mm/segment.h"
#include "mm/kmem.h"
#include "io/device.h"
#include "io/pci.h"
#include "io/ata.h"
#include "io/serial.h"
#include "io/framebuffer.h"
#include "irq/interrupt.h"
#include "irq/pic.h"
#include "irq/rtc.h"
#include "util/string.h"
#include "util/multiboot.h"
#include "util/log.h"

static char buf[ATAPISectorSize];

int kmain(multiboot_info_t *mbi) {
    initSegment();
    initInterrupt();
    initKmem();
    initDevice();

    device_t *com1 = initSerial(SerialCOM1);
    device_t *fb = initFB();
    klogSetDevice(fb);
    klog("log start");

    initPIC();
    initRTC();

    initPCI();
    initATA();

    char *str = "hello world!\n";
    int len = strlen(str);
    deviceWrite(fb, str, len);
    deviceWrite(com1, str, len);

    mbi = mbi;

    __asm__("int3\n");

    sti();

    ata_device_t *cdrom = ataDevices[1];
    if (atapiRead(cdrom, buf, 0, 1)) {
        klog("read complete!");
    }

    for (;;) {
        hlt();
    }

    return 0;
}
