#include "mm/kmem.h"

static kptr_t kbrk;
static kmem_cache_t kCache[kmemCacheSize];

void kmemInit() {
    kbrk = &kBSSEnd;
}

void *ksbrk(size_t size) {
    size = kmemAlign(size);
    void *ret = kbrk;
    kbrk += size;
    return ret;
}

void kmemInitCache(int cache, size_t size, ctor_t ctor) {
    size = kmemAlign(size);
    kCache[cache].head = NULL;
    kCache[cache].size = size;
    kCache[cache].ctor = ctor;
}

void *kalloc(int cache) {
    size_t size = kCache[cache].size;
    ctor_t ctor = kCache[cache].ctor;
    if (!kCache[cache].head) {
        void *ret = ksbrk(size);
        if (ctor) ctor(ret, size);
        return ret;
    } else {
        kptr_t ret = kCache[cache].head;
        kCache[cache].head = kmemNext(ret);
        if (ctor) ctor(ret, size);
        return ret;
    }
}

void kfree(int cache, void *ptr) {
    kmemNext(ptr) = kCache[cache].head;
    kCache[cache].head = (kptr_t) ptr;
}
