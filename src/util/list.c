#include "util/list.h"

void listAppend(list_t *now, list_t *prev) {
    list_t *next = prev -> next;
    prev -> next = now;
    now -> prev = prev;
    next -> prev = now;
    now -> next = next;
}

void listDelete(list_t *now) {
    now -> next -> prev = now -> prev;
    now -> prev -> next = now -> next;
}
