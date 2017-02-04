#ifndef __RAMFS
#define __RAMFS

#include "fs/fs.h"
#include "fs/superblock.h"
#include "fs/vnode.h"

#define RAMFSName       "ramfs"

superblock_t *ramfsReadSuperblock(superblock_t *sb, vnode_t *vnode);
vnode_t *ramfsReleaseNode(vnode_t *vnode);

#endif
