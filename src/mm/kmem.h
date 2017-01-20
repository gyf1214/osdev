#ifndef __KMEM
#define __KMEM

#include "util/type.h"

#define kmemCacheSize   16
#define kmemAlignSize   4
#define kmemAlign(x)    (((x) + kmemAlignSize - 1) & -kmemAlignSize)
#define kmemNext(x)     (*((kptr_t *)(x)))

#define kmemDevice      0

typedef char *kptr_t;
typedef void (*ctor_t)(void *, size_t);

typedef struct kmem_cache {
    kptr_t head;
    size_t size;
    ctor_t ctor;
}kmem_cache_t;

extern char kBSSEnd;

void initKmem(void);
void kmemInitCache(int cache, size_t size, ctor_t ctor);
void *ksbrk(size_t);
void *kalloc(int cache);
void kfree(int cache, void *ptr);

#endif
