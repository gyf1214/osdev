#ifndef __LIST
#define __LIST

#include "util/type.h"

#define listEntry(ptr, type, member)    MemberContainer(ptr, type, member)
#define listInit(name)                  (name) = { .next = &(name), .prev = &(name) }

typedef struct list {
    struct list *next;
    struct list *prev;
}list_t;

void listAppend(list_t *now, list_t *prev);
void listDelete(list_t *now);

#endif
