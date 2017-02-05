#ifndef __FILE
#define __FILE

#include "util/type.h"
#include "fs/vnode.h"
#include "fs/superblock.h"

typedef struct file {
    vnode_t *vnode;
    superblock_t *sb;
    offset_t offset;
}file_t;

file_t *fileOpen(vnode_t *vnode);
ssize_t fileRead(file_t *file, void *buf, size_t size);
ssize_t fileWrite(file_t *file, const void *buf, size_t size);

#endif
