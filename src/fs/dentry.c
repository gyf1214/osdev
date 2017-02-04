#include "fs/dentry.h"
#include "fs/vnode.h"
#include "fs/superblock.h"
#include "fs/fs.h"
#include "mm/kmem.h"
#include "util/string.h"

int dentryCompareName(dentry_t *dentry, const char *name) {
    if (dentry -> sb -> fs -> compareName) {
        return dentry -> sb -> fs -> compareName(dentry -> name, name);
    } else {
        return strcmp(dentry -> name, name);
    }
}

void dentryCtor(void *ptr, size_t size) {
    memset(ptr, 0, size);
    dentry_t *dentry = ptr;
    listInit(&dentry -> dentryList);
}

dentry_t *dentryAlloc(vnode_t *vnode, const char *name) {
    dentry_t *dentry = kalloc(KmemDentry);
    dentry -> vnode = vnodeLink(vnode);
    dentry -> sb = vnode -> sb;
    strncpy(dentry -> name, name, DentryNameLength);

    return dentry;
}

void dentryDelete(dentry_t *dentry) {
    listDelete(&dentry -> dentryList);
    vnodeUnlink(dentry -> vnode);

    kfree(KmemDentry, dentry);
}
