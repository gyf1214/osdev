#ifndef __ROOTFS
#define __ROOTFS

#include "fs/vnode.h"

#define RootfsName      "rootfs"

vnode_t *initRootfs(void);

#endif
