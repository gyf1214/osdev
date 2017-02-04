#include "fs/ramfs/ramfs.h"
#include "util/type.h"

superblock_t *ramfsReadSuperblock(superblock_t *sb, vnode_t *vnode) {
    Unused(vnode);

    sb -> root = vnodeLink(vnodeAlloc(sb));
    return sb;
}

vnode_t *ramfsReleaseNode(vnode_t *vnode) {
    return vnode;
}
