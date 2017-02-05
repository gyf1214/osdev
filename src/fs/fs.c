#include "fs/fs.h"
#include "fs/vnode.h"
#include "fs/dentry.h"
#include "fs/superblock.h"
#include "fs/file.h"
#include "fs/rootfs/rootfs.h"
#include "fs/devfs/devfs.h"
#include "mm/kmem.h"
#include "util/string.h"

static fs_t *fsList = NULL;
vnode_t *fsRoot = NULL;

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

vnode_t *fsLoad(fs_t *fs, vnode_t *device) {
    superblock_t *sb = superblockAlloc(fs, device);
    if (!fs -> readSuperblock(sb, device)) {
        kfree(KmemSuperBlock, sb);
        return NULL;
    } else {
        return sb -> mount = sb -> root;
    }
}

vnode_t *fsMountAt(fs_t *fs, vnode_t *device, vnode_t *parent, const char *name) {
    if (!vnodeOpen(parent)) return NULL;
    vnode_t *root = fsLoad(fs, device);
    if (!root) return NULL;
    root -> sb -> mount = parent;
    dentry_t *rootEntry = dentryAlloc(root, name);
    vnodeAppendDentry(parent, rootEntry);
    return root;
}

void initFS() {
    kmemInitCache(KmemVnode, sizeof(vnode_t), vnodeCtor);
    kmemInitCache(KmemDentry, sizeof(dentry_t), dentryCtor);
    kmemInitCache(KmemSuperBlock, sizeof(superblock_t), superblockCtor);
    kmemInitCache(KmemFS, sizeof(fs_t), kmemDefaultCtor);
    kmemInitCache(KmemFile, sizeof(file_t), kmemDefaultCtor);

    fsRoot = initRootfs();
    initDevfs();
}
