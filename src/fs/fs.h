#ifndef __FS
#define __FS

#include "util/type.h"

struct vnode;
struct dentry;
struct superblock;

typedef struct fs {
    uint32_t inodeCount;
    const char *name;
    struct fs *next;
    struct superblock *(*mount)(struct vnode *);
    struct vnode *(*initNode)(struct vnode *);
    struct vnode *(*releaseNode)(struct vnode *);
}fs_t;

void fsRegister(fs_t *fs);
void initFS(void);

#endif
