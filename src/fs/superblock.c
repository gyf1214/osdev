#include "fs/superblock.h"
#include "fs/vnode.h"
#include "util/string.h"

void superblockCtor(void *ptr, size_t size) {
    memset(ptr, 0, size);
    superblock_t *sb = ptr;
    listInit(&sb -> vnodeList);
}

void superblockAppendVnode(superblock_t *sb, vnode_t *vnode) {
    listAppend(&sb -> vnodeList, &vnode -> vnodeList);
}
