#include "fs/vnode.h"
#include "fs/dentry.h"
#include "fs/superblock.h"
#include "fs/fs.h"
#include "mm/kmem.h"
#include "util/string.h"

vnode_t *vnodeOpen(vnode_t *vnode) {
    vnode_t *ret = vnode;
    if (!(vnode -> flags & VnodePresent)) {
        ret = vnodeInit(vnode);
    }
    if (ret) {
        ++vnode -> refcount;
    }
    return ret;
}

vnode_t *vnodeClose(vnode_t *vnode) {
    vnode_t *ret = vnode;
    if (--vnode -> refcount <= 0) {
        ret = vnodeRelease(vnode);
    }
    return ret;
}

vnode_t *vnodeLink(vnode_t *vnode) {
    ++vnode -> dcount;
    return vnode;
}

void vnodeUnlink(vnode_t *vnode) {
    if (--vnode -> dcount <= 0 && !(vnode -> flags & VnodePresent)) {
        vnodeDelete(vnode);
    }
}

vnode_t *vnodeInit(vnode_t *vnode) {
    if (vnode -> sb -> fs -> initNode) {
        return vnode -> sb -> fs -> initNode(vnode);
    } else {
        if (vnode -> sb -> fs -> readNode) {
            if (!vnode -> sb -> fs -> readNode(vnode)) {
                return NULL;
            }
        }
        vnode -> flags |= VnodePresent;
        return vnode;
    }
}

vnode_t *vnodeRelease(vnode_t *vnode) {
    if (vnode -> sb -> fs -> releaseNode) {
        return vnode -> sb -> fs -> releaseNode(vnode);
    } else {
        vnode_t *ret = vnodeWrite(vnode);
        vnode -> flags &= (~VnodePresent);
        vnodeClearDentry(vnode);
        return ret;
    }
}

vnode_t *vnodeWrite(vnode_t *vnode) {
    vnode_t *ret = vnode;
    if (vnode -> sb -> fs -> writeNode) {
        ret = vnode -> sb -> fs -> writeNode(vnode);
    }
    if (ret) {
        vnode -> flags &= (~VnodeDirty);
    }
    return ret;
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
