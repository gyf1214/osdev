#include "fs/superblock.h"
#include "fs/vnode.h"
#include "fs/fs.h"
#include "mm/kmem.h"
#include "util/string.h"

void superblockCtor(void *ptr, size_t size) {
    memset(ptr, 0, size);
    superblock_t *sb = ptr;
    listInit(&sb -> vnodeList);
}

superblock_t *superblockAlloc(fs_t *fs, vnode_t *device) {
    superblock_t *sb = kalloc(KmemSuperBlock);
    sb -> fs = fs;
    sb -> device = device;
    return sb;
}

void superblockAppendVnode(superblock_t *sb, vnode_t *vnode) {
    listAppend(&sb -> vnodeList, &vnode -> vnodeList);
}
