#include "fs/devfs/devfs.h"
#include "fs/ramfs/ramfs.h"
#include "fs/fs.h"

vnode_t *devRoot = NULL;

void initDevfs() {
    fs_t *devfs = fsAlloc(DevfsName);
    devfs -> readSuperblock = ramfsReadSuperblock;
    devfs -> releaseNode = ramfsReleaseNode;
    devfs -> readNode = ramfsReadNode;
    fsRegister(devfs);

    devRoot = vnodeOpen(fsMountAt(devfs, NULL, fsRoot, DevfsMountPoint));
}
