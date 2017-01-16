#include "mm/segment.h"
#include "io/dev.h"
#include "util/string.h"

int kmain() {
    initSegment();
    initDev();

    char *str = "hello world!\n";
    devWrite(&devCOM1, str, strlen(str));

    return 0;
}
