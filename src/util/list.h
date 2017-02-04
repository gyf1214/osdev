#ifndef __LIST
#define __LIST

#include "util/type.h"

#define listEntry(ptr, type, member)    MemberContainer(ptr, type, member)

typedef struct list {
    struct list *next;
    struct list *prev;
}list_t;

void listInit(list_t *now);
void listAppend(list_t *now, list_t *prev);
void listDelete(list_t *now);
int listEmpty(list_t *now);

#endif
