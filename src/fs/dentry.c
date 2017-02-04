#include "fs/dentry.h"
#include "fs/vnode.h"
#include "mm/kmem.h"
#include "util/string.h"

void dentryCtor(void *ptr, size_t size) {
    memset(ptr, 0, size);
    dentry_t *dentry = (dentry_t *)ptr;
    listInit(&dentry -> dentryList);
}

void dentryDelete(dentry_t *dentry) {
    listDelete(&dentry -> dentryList);
    vnodeUnlink(dentry -> vnode);

    kfree(KmemDentry, dentry);
}
