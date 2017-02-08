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
#include "fs/vnode.h"
#include "fs/file.h"
#include "fs/fs.h"
#include "util/string.h"
#include "util/multiboot.h"
#include "util/log.h"

static char buf[ATAPISectorSize];

static void beforeFS() {
    initSegment();
    initInterrupt();
    initKmem();
}

static void initLog() {
    file_t *logger = fileOpen(fsGetFile(fsRoot, "dev/com1"));
    klogSetFile(logger);
    klog("log start");
}

static void afterFS() {
    initDevice();
    initLog();
    initPIC();
    initRTC();
    initPCI();
    initATA();
}

static void tests() {
    file_t *fb = fileOpen(fsGetFile(fsRoot, "dev/fb"));
    char *str = "hello world!\n";
    int len = strlen(str);
    fileWrite(fb, str, len);

    __asm__("int3\n");

    ata_device_t *cdrom = ataDevices[1];
    if (atapiRead(cdrom, buf, 0, 1)) {
        klog("read complete!");
    }
}

int kmain(multiboot_info_t *mbi) {
    Unused(mbi);

    beforeFS();
    initFS();
    afterFS();

    sti();

    tests();

    for (;;) {
        hlt();
    }

    return 0;
}
