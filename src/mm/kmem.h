#ifndef __KMEM
#define __KMEM

#include "util/type.h"

#define KmemCacheLength 16
#define KmemAlignSize   4
#define KmemAlign(x)    (((x) + KmemAlignSize - 1) & -KmemAlignSize)
#define KmemNext(x)     (*((kptr_t *)(x)))

#define KmemDevice      0
#define KmemPCI         1
#define KmemATAChannel  2
#define KmemATADevice   3
#define KmemFS          4
#define KmemVnode       5
#define KmemDentry      6

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
void kmemDefaultCtor(void *ptr, size_t size);
void *ksbrk(size_t);
void *kalloc(int cache);
void kfree(int cache, void *ptr);

#endif
