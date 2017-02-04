#ifndef __SUPERBLOCK
#define __SUPERBLOCK

#include "util/type.h"
#include "util/list.h"

struct dentry;
struct vnode;
struct fs;

typedef struct superblock {
    struct fs *fs;
    list_t vnodeList;
    struct vnode *root;
    struct vnode *device;
}superblock_t;

void superblockCtor(void *ptr, size_t size);
superblock_t *superblockAlloc(struct fs *fs, struct vnode *device);
void superblockAppendVnode(superblock_t *sb, struct vnode *vnode);

#endif
