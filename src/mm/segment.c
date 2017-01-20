#include "mm/segment.h"

static gdt_t gdt[SegLength];

static gdtr_t gdtr;

void segSet(int index, uint32_t base, size_t limit, uint16_t flag) {
    limit >>= 12;

    uint64_t desc;

    desc    =   limit       & 0x000f0000;
    desc   |=  (flag << 8)  & 0x00f0ff00;
    desc   |=  (base >> 16) & 0x000000ff;
    desc   |=   base        & 0xff000000;
    desc  <<=   32;
    desc   |=   base << 16;
    desc   |=   limit       & 0x0000ffff;

    gdt[index] = desc;
}

void initSegment() {
    segSet(0, 0, 0, 0);
    segSet(1, 0, 0xffffffff, SegCodeSys);
    segSet(2, 0, 0xffffffff, SegDataSys);
    segSet(3, 0, 0xffffffff, SegCodeUsr);
    segSet(4, 0, 0xffffffff, SegDataUsr);

    gdtr.address = (uint32_t)gdt;
    gdtr.limit = SegLength * sizeof(gdt_t);
    lgdt(&gdtr);

    segLoadDS(SegSelDataSys);
    segLoadES(SegSelDataSys);
    segLoadFS(SegSelDataSys);
    segLoadGS(SegSelDataSys);
    segLoadSS(SegSelDataSys);
    segLoadCS(SegSelCodeSys);
}
