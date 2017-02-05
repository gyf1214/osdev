#include "fs/ramfs/ramfs.h"
#include "fs/dentry.h"
#include "util/type.h"

superblock_t *ramfsReadSuperblock(superblock_t *sb, vnode_t *vnode) {
    Unused(vnode);

    sb -> root = vnodeLink(vnodeAlloc(sb));
    return sb;
}

vnode_t *ramfsReleaseNode(vnode_t *vnode) {
    return vnode;
}

vnode_t *ramfsAllocNode(superblock_t *sb) {
    vnode_t *vnode = vnodeAlloc(sb);
    vnode -> flags |= VnodePresent;

    return vnode;
}

vnode_t *ramfsReadNode(vnode_t *vnode) {
    vnodeInitDir(vnode, vnode -> sb -> mount);
    return vnode;
}
