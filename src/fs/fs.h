#ifndef __FS
#define __FS

#include "util/type.h"

#define FSNameLength    16

struct vnode;
struct dentry;
struct superblock;

typedef struct fs {
    char name[FSNameLength];
    struct fs *next;
    struct superblock *(*readSuperblock)(struct superblock *, struct vnode *);
    struct vnode *(*initNode)(struct vnode *);
    struct vnode *(*releaseNode)(struct vnode *);
    struct vnode *(*readNode)(struct vnode *);
    struct vnode *(*writeNode)(struct vnode *);
}fs_t;

void fsRegister(fs_t *fs);
fs_t *fsAlloc(const char *name);
fs_t *fsFind(const char *name);
struct vnode *fsMount(fs_t *fs, struct vnode *);
void initFS(void);

#endif
