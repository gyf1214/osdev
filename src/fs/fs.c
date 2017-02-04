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

fs_t *fsAlloc(const char *name) {
    fs_t *fs = kalloc(KmemFS);
    strncpy(fs -> name, name, FSNameLength);
    return fs;
}

fs_t *fsFind(const char *name) {
    for (fs_t *fs = fsList; fs; fs = fs -> next) {
        if (!strcmp(fs -> name, name)) {
            return fs;
        }
    }
    return NULL;
}

dentry_t *fsMount(fs_t *fs, vnode_t *vnode) {
    superblock_t *sb = superblockAlloc(fs);
    if (!fs -> readSuperblock(sb, vnode)) {
        kfree(KmemSuperBlock, sb);
        return NULL;
    } else {
        return sb -> root;
    }
}

void initFS() {
    kmemInitCache(KmemVnode, sizeof(vnode_t), vnodeCtor);
    kmemInitCache(KmemDentry, sizeof(dentry_t), dentryCtor);
    kmemInitCache(KmemSuperBlock, sizeof(superblock_t), superblockCtor);
    kmemInitCache(KmemFS, sizeof(fs_t), kmemDefaultCtor);
}
