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

void dentryCtor(void *ptr, size_t size);
dentry_t *dentryAlloc(vnode_t *vnode);
void dentryDelete(dentry_t *dentry);

#endif
