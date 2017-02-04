#include "fs/vnode.h"
#include "fs/dentry.h"
#include "fs/superblock.h"
#include "fs/fs.h"
#include "mm/kmem.h"
#include "util/string.h"

vnode_t *vnodeOpen(vnode_t *vnode) {
    if (!(vnode -> flags & VnodePresent)) {
        vnodeInit(vnode);
    }
    ++vnode -> refcount;

    return vnode;
}

void vnodeClose(vnode_t *vnode) {
    if (--vnode -> refcount <= 0) {
        vnodeRelease(vnode);
    }
}

vnode_t *vnodeLink(vnode_t *vnode) {
    ++vnode -> dcount;
    return vnode;
}

void vnodeUnlink(vnode_t *vnode) {
    if (--vnode -> dcount <= 0 && !(vnode -> flags & VnodePresent)) {

    }
}

void vnodeInit(vnode_t *vnode) {
    if (vnode -> sb -> fs -> initNode) {
        vnode -> sb -> fs -> initNode(vnode);
    }
}

void vnodeRelease(vnode_t *vnode) {
    if (vnode -> sb -> fs -> releaseNode) {
        vnode -> sb -> fs -> releaseNode(vnode);
    }
}

void vnodeAppendDentry(vnode_t *vnode, dentry_t *dentry) {
    listAppend(&vnode -> dentryList, &dentry -> dentryList);
}

void vnodeClearDentry(vnode_t *vnode) {
    list_t *now = vnode -> dentryList.next;
    listInit(&vnode -> dentryList);
    while (!listEmpty(now)) {
        list_t *next = now -> next;
        dentryDelete(listEntry(now, dentry_t, dentryList));
        now = next;
    }
}

void vnodeCtor(void *ptr, size_t size) {
    memset(ptr, 0, size);
    vnode_t *vnode = ptr;
    listInit(&vnode -> vnodeList);
    listInit(&vnode -> dentryList);
}

vnode_t *vnodeAlloc(superblock_t *sb) {
    vnode_t *vnode = kalloc(KmemVnode);
    vnode -> sb = sb;
    superblockAppendVnode(sb, vnode);

    return vnode;
}

void vnodeDelete(vnode_t *vnode) {
    vnodeClearDentry(vnode);
    listDelete(&vnode -> vnodeList);

    kfree(KmemVnode, vnode);
}
