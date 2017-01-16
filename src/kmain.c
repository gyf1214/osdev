#include "mm/segment.h"
#include "io/device.h"
#include "io/framebuffer.h"
#include "util/string.h"

int kmain() {
    initSegment();
    initDevice();

    char *str = "hello world!\n";
    int len = strlen(str);
    deviceWrite(&deviceCOM1, str, len);
    deviceWrite(&deviceFB, str, len);

    return 0;
}
