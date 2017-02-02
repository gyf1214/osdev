#ifndef __PAGE
#define __PAGE

#include "util/type.h"

typedef uint32_t                pte_t;

extern pte_t kpdt[];

#define PagePack(addr, flag)    ((((uint32_t)(addr)) & 0xfffff000) & ((flag) & 0xfff))
#define PagePresent             0x1
#define PageRW                  0x2
#define PageUser                0x4
#define PageSizeExt             0x80
#define PageSysR                PagePresent
#define PageSysRW               PagePresent | PageRW
#define PageUsrR                PagePresent | PageUser
#define PageUsrRW               PagePresent | PageUser | PageRW

void pageLoadCR3(uint32_t addr);
void pageFlushTLB(uint32_t addr);

#endif
