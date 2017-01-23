#include "irq/interrupt.h"
#include "util/string.h"
#include "util/log.h"

static idt_t idt[IntLength];

static idtr_t idtr;

void initInterrupt() {
    memset(idt, 0, IntLength * sizeof(idt_t));
    IntSet(03, IntInteSys);
    IntSet(40, IntInteSys);

    idtr.limit = IntLength * sizeof(idt_t);
    idtr.address = (uint32_t) idt;
    lidt(&idtr);
}

void intSetDesc(int index, uint32_t addr, uint16_t flag) {
    uint64_t desc;

    desc    =   flag            & 0x0000ffff;
    desc   |=   addr            & 0xffff0000;
    desc  <<=   32;
    desc   |=  (IntSel << 16)   & 0xffff0000;
    desc   |=   addr            & 0x0000ffff;

    idt[index] = desc;
}

void intDebugHandler() {
    klog("int 0x03 triggered!");
}
