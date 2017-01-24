#ifndef __PORT
#define __PORT

#include "util/type.h"

void outb(uint16_t port, uint8_t data);
void outw(uint16_t port, uint16_t data);
void outl(uint16_t port, uint32_t data);

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void insb(uint16_t port, uint8_t *buf, size_t count);
void insw(uint16_t port, uint16_t *buf, size_t count);
void insl(uint16_t port, uint32_t *buf, size_t count);

void outsb(uint16_t port, uint8_t *buf, size_t count);
void outsw(uint16_t port, uint16_t *buf, size_t count);
void outsl(uint16_t port, uint32_t *buf, size_t count);

void ioWait(void);

#endif
