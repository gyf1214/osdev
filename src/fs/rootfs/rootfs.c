#include "fs/rootfs/rootfs.h"
#include "fs/ramfs/ramfs.h"
#include "fs/fs.h"

vnode_t *initRootfs() {
    fs_t *rootfs = fsAlloc(RootfsName);
    rootfs -> readSuperblock = ramfsReadSuperblock;
    rootfs -> releaseNode = ramfsReleaseNode;
    rootfs -> readNode = ramfsReadNode;
    fsRegister(rootfs);

    return fsLoad(rootfs, NULL);
}
