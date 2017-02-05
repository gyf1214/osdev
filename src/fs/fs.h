#ifndef __FS
#define __FS

#include "util/type.h"

#define FSNameLength    16

struct vnode;
struct dentry;
struct superblock;
struct file;

typedef struct fs {
    char name[FSNameLength];
    struct fs *next;
    struct superblock *(*readSuperblock)(struct superblock *, struct vnode *);
    struct vnode *(*initNode)(struct vnode *);
    struct vnode *(*releaseNode)(struct vnode *);
    struct vnode *(*readNode)(struct vnode *);
    struct vnode *(*writeNode)(struct vnode *);
    int (*compareName)(const char *s1, const char *s2);
    ssize_t (*readFile)(struct vnode *, void *buf, size_t size, offset_t *offset);
    ssize_t (*writeFile)(struct vnode *, const void *buf, size_t size, offset_t *offset);
}fs_t;

extern struct vnode *fsRoot;

void fsRegister(fs_t *fs);
fs_t *fsAlloc(const char *name);
fs_t *fsFind(const char *name);
struct vnode *fsLoad(fs_t *fs, struct vnode *device);
struct vnode *fsMountAt(fs_t *fs, struct vnode *device,
                        struct vnode *parent, const char *name);
void initFS(void);

#endif
