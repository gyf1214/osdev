#include "util/list.h"

void listInit(list_t *now) {
    now -> next = now -> prev = now;
}

void listAppend(list_t *prev, list_t *now) {
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

int listEmpty(list_t *now) {
    return now -> next == now;
}
