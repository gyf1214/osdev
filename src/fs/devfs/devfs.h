#ifndef __DEVFS
#define __DEVFS

#include "fs/vnode.h"
#include "io/device.h"

#define DevfsName       "devfs"
#define DevfsMountPoint "dev"

extern vnode_t *devRoot;

void initDevfs(void);
void devfsMountDevice(vnode_t *parent, const char *name, device_t *dev);
ssize_t devfsReadFile(vnode_t *vnode, void *buf,
                      size_t size, offset_t *offset);
ssize_t devfsWriteFile(vnode_t *vnode, const void *buf,
                       size_t size, offset_t *offset);

#endif
