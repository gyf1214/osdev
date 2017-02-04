#ifndef __VNODE
#define __VNODE

#include "util/type.h"
#include "util/list.h"

#define VnodePresent    0x01
#define VnodeDirty      0x02

struct dentry;
struct superblock;

typedef struct vnode {
    uint32_t info;
    uint32_t flags;
    int refcount, dcount;
    list_t dentryList;
    struct superblock *sb;
    list_t vnodeList;
}vnode_t;

vnode_t *vnodeOpen(vnode_t *vnode);
vnode_t *vnodeClose(vnode_t *vnode);
vnode_t *vnodeLink(vnode_t *vnode);
void vnodeUnlink(vnode_t *vnode);
vnode_t *vnodeInit(vnode_t *vnode);
vnode_t *vnodeRelease(vnode_t *vnode);
vnode_t *vnodeWrite(vnode_t *vnode);
struct dentry *vnodeFindDentry(vnode_t *vnode, const char *name);
void vnodeAppendDentry(vnode_t *vnode, struct dentry *dentry);
void vnodeClearDentry(vnode_t *vnode);
void vnodeCtor(void *ptr, size_t size);
vnode_t *vnodeAlloc(struct superblock *sb);
void vnodeDelete(vnode_t *vnode);

#endif
