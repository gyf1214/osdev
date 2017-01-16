#include "mm/segment.h"
#include "io/dev.h"
#include "io/framebuffer.h"
#include "util/string.h"

int kmain() {
    initSegment();
    initDev();

    char *str = "hello world!\n";
    int len = strlen(str);
    devWrite(&devCOM1, str, len);
    devWrite(&devFramebuffer, str, len);

    return 0;
}
