#include "fs/dentry.h"
#include "fs/vnode.h"
#include "mm/kmem.h"
#include "util/string.h"

void dentryCtor(void *ptr, size_t size) {
    memset(ptr, 0, size);
    dentry_t *dentry = ptr;
    listInit(&dentry -> dentryList);
}

dentry_t *dentryAlloc(vnode_t *vnode, const char *name) {
    dentry_t *dentry = kalloc(KmemDentry);
    dentry -> vnode = vnodeLink(vnode);
    strncpy(dentry -> name, name, DentryNameLength);
}

void dentryDelete(dentry_t *dentry) {
    listDelete(&dentry -> dentryList);
    vnodeUnlink(dentry -> vnode);

    kfree(KmemDentry, dentry);
}
