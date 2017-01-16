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
    segSet(3, 0xc0000000, 0xffffffff, SegCodeSys);
    segSet(4, 0xc0000000, 0xffffffff, SegDataSys);
    segSet(5, 0, 0xffffffff, SegCodeUsr);
    segSet(6, 0, 0xffffffff, SegDataUsr);

    gdtr.address = (uint32_t)gdt;
    gdtr.limit = SegLength * sizeof(gdt_t);
    segLoadGDT(&gdtr);

    uint16_t sel = SegSel(2, SegSelSys);
    segLoadDS(sel);
    segLoadES(sel);
    segLoadFS(sel);
    segLoadGS(sel);
    segLoadSS(sel);
    segLoadCS(SegSel(1, SegSelSys));
}
