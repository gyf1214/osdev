#include "util/log.h"
#include "util/string.h"

static file_t *logger = NULL;

void klogSetFile(file_t *file) {
    logger = file;
}

void klog(const char *line) {
    if (!logger) return;
    int len = strlen(line);
    fileWrite(logger, line, len);
    fileWrite(logger, "\n", 1);
}
