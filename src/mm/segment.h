#ifndef __SEGMENT
#define __SEGMENT

#include "util/type.h"

#define SegDesc     (1 << 4)
#define SegPres     (1 << 7)
#define SegSavl     (1 << 12)
#define SegLong     (1 << 13)
#define SegSize     (1 << 14)
#define SegGran     (1 << 15)
#define SegPriv(x)  (((x) & 0x3) << 5)

#define SegDataR    0x0
#define SegDataRW   0x2
#define SegDataRD   0x4
#define SegDataRDW  0x6
#define SegCodeX    0x8
#define SegCodeRX   0xa
#define SegCodeRC   0xc
#define SegCodeRXC  0xe

#define SegComm     SegDesc | SegPres    | SegSize | SegGran
#define SegCodeSys  SegComm | SegPriv(0) | SegCodeRX
#define SegDataSys  SegComm | SegPriv(0) | SegDataRW
#define SegCodeUsr  SegComm | SegPriv(3) | SegCodeRX
#define SegDataUsr  SegComm | SegPriv(3) | SegDataRW

#define SegLength   5

#define SegSelSys   0
#define SegSelUsr   3
#define SegSel(i, flag)  (((i) << 3) | (flag))

typedef uint64_t    gdt_t;

typedef struct gdtr {
    uint16_t limit;
    uint32_t address;
} __attribute__((packed)) gdtr_t;

void initSegment(void);
void segSet(int index, uint32_t base, size_t limit, uint16_t flag);
void segLoadDS(uint16_t sel);
void segLoadES(uint16_t sel);
void segLoadFS(uint16_t sel);
void segLoadGS(uint16_t sel);
void segLoadSS(uint16_t sel);
void segLoadCS(uint16_t sel);
void segLoadGDT(gdtr_t *gdtr);

#endif
