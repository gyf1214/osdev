#ifndef __DENTRY
#define __DENTRY

#include "util/type.h"
#include "util/list.h"

#define DentryNameLength    32
#define DentryNameThis      "."
#define DentryNameParent    ".."

struct vnode;
struct superblock;

typedef struct dentry {
    char name[DentryNameLength];
    uint32_t flags;
    struct vnode *vnode;
    struct superblock *sb;
    list_t dentryList;
}dentry_t;

int dentryCompareName(dentry_t *dentry, const char *name);
void dentryCtor(void *ptr, size_t size);
dentry_t *dentryAlloc(struct vnode *vnode, const char *name);
void dentryDelete(dentry_t *dentry);

#endif
