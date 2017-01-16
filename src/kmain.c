#include "mm/segment.h"
#include "io/dev.h"
#include "io/framebuffer.h"
#include "util/string.h"

int kmain() {
    initSegment();
    initDev();

    char *str = "hello world!\n";
    devWrite(&devCOM1, str, strlen(str));

    fbClear();

    int i, j;
    for (i = 0; i < 26; ++i) {
        for (j = 0; j < i; ++j) fbPutChar('A' + j);
        fbPutChar('\n');
    }
    fbScroll();

    return 0;
}
