#include "fs/devfs/devfs.h"
#include "fs/ramfs/ramfs.h"
#include "fs/dentry.h"
#include "fs/fs.h"

vnode_t *devRoot = NULL;

void initDevfs() {
    fs_t *devfs = fsAlloc(DevfsName);
    devfs -> readSuperblock = ramfsReadSuperblock;
    devfs -> releaseNode = ramfsReleaseNode;
    devfs -> readNode = ramfsReadNode;
    devfs -> readFile = devfsReadFile;
    devfs -> writeFile = devfsWriteFile;
    fsRegister(devfs);

    devRoot = fsMountAt(devfs, NULL, fsRoot, DevfsMountPoint);
    vnodeInit(devRoot);
}

void devfsMountDevice(vnode_t *parent, const char *name, device_t *device) {
    vnode_t *vnode = ramfsAllocNode(devRoot -> sb);
    vnode -> info = (uint32_t)device;

    dentry_t *dentry = dentryAlloc(vnode, name);
    vnodeAppendDentry(parent, dentry);
}

ssize_t devfsReadFile(vnode_t *vnode, void *buf,
                      size_t size, offset_t *offset) {
    Unused(offset);
    device_t *dev = (device_t *)vnode -> info;
    return deviceRead(dev, buf, size);
}

ssize_t devfsWriteFile(vnode_t *vnode, const void *buf,
                       size_t size, offset_t *offset) {
    Unused(offset);
    device_t *dev = (device_t *)vnode -> info;
    return deviceWrite(dev, buf, size);
}
