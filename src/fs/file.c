#include "fs/file.h"
#include "fs/fs.h"
#include "mm/kmem.h"

file_t *fileOpen(vnode_t *vnode) {
    file_t *file = kalloc(KmemFile);
    file -> vnode = vnodeOpen(vnode);
    file -> sb = vnode -> sb;
    if (!file -> vnode) {
        kfree(KmemFile, file);
        return NULL;
    }
    return file;
}

ssize_t fileRead(file_t *file, void *buf, size_t size) {
    if (file -> sb -> fs -> readFile) {
        return file -> sb -> fs -> readFile(file -> vnode, buf, size, &file -> offset);
    } else {
        return -1;
    }
}

ssize_t fileWrite(file_t *file, const void *buf, size_t size) {
    if (file -> sb -> fs -> writeFile) {
        return file -> sb -> fs -> writeFile(file -> vnode, buf, size, &file -> offset);
    } else {
        return -1;
    }
}
