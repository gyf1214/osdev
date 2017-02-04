#include "fs/fs.h"
#include "fs/vnode.h"
#include "fs/dentry.h"
#include "fs/superblock.h"
#include "mm/kmem.h"
#include "util/string.h"

static fs_t *fsList = NULL;

void fsRegister(fs_t *fs) {
    fs -> next = fsList;
    fsList = fs;
}

static void initRootFS() {
    fs_t *rootfs = kalloc(KmemFS);
}

void initFS() {
    kmemInitCache(KmemVnode, sizeof(vnode_t), vnodeCtor);
    kmemInitCache(KmemDentry, sizeof(dentry_t), dentryCtor);
    kmemInitCache(KmemSuperBlock, sizeof(superblock_t), superblockCtor);
    kmemInitCache(KmemFS, sizeof(fs_t), kmemDefaultCtor);

    initRootFS();
}
