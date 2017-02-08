#ifndef __LOG
#define __LOG

#include "fs/file.h"

void klogSetFile(file_t *file);
void klog(const char *line);

#endif
