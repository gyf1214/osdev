#include "mm/segment.h"
#include "io/device.h"
#include "io/framebuffer.h"
#include "util/string.h"
#include "util/multiboot.h"

int kmain(multiboot_info_t *mbi) {
    initSegment();
    initDevice();

    char *str = "hello world!\n";
    int len = strlen(str);
    deviceWrite(&deviceCOM1, str, len);
    deviceWrite(&deviceFB, str, len);

    mbi = mbi;

    return 0;
}
