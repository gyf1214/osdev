#include "fs/fs.h"
#include "fs/vnode.h"
#include "fs/dentry.h"
#include "fs/superblock.h"
#include "fs/rootfs/rootfs.h"
#include "mm/kmem.h"
#include "util/string.h"

static fs_t *fsList = NULL;
static vnode_t *fsRootNode;

void fsRegister(fs_t *fs) {
    fs -> next = fsList;
    fsList = fs;
}

fs_t *fsAlloc(const char *name) {
    fs_t *fs = kalloc(KmemFS);
    strncpy(fs -> name, name, FSNameLength);
    return fs;
}

fs_t *fsFind(const char *name) {
    fs_t *fs;
    for (fs = fsList; fs; fs = fs -> next) {
        if (!strcmp(fs -> name, name)) {
            return fs;
        }
    }
    return NULL;
}

vnode_t *fsMount(fs_t *fs, vnode_t *device) {
    superblock_t *sb = superblockAlloc(fs, device);
    if (!fs -> readSuperblock(sb, device)) {
        kfree(KmemSuperBlock, sb);
        return NULL;
    } else {
        return sb -> root;
    }
}

vnode_t *fsRoot() {
    return fsRootNode;
}

void initFS() {
    kmemInitCache(KmemVnode, sizeof(vnode_t), vnodeCtor);
    kmemInitCache(KmemDentry, sizeof(dentry_t), dentryCtor);
    kmemInitCache(KmemSuperBlock, sizeof(superblock_t), superblockCtor);
    kmemInitCache(KmemFS, sizeof(fs_t), kmemDefaultCtor);

    fsRootNode = initRootfs();
}
