#ifndef __INTERRUPT
#define __INTERRUPT

#include "util/type.h"
#include "mm/segment.h"

#define IntPres         (1 << 15)
#define IntPriv(x)      (((x) & 0x3) << 13)
#define IntTask         0x500
#define IntInte         0xe00
#define IntTrap         0xf00
#define IntSel          SegSelCodeSys

#define IntTaskSys      IntPres | IntPriv(0) | IntTask
#define IntInteSys      IntPres | IntPriv(0) | IntInte
#define IntTrapSys      IntPres | IntPriv(0) | IntTrap
#define IntTaskUsr      IntPres | IntPriv(3) | IntTask
#define IntInteUsr      IntPres | IntPriv(3) | IntInte
#define IntTrapUsr      IntPres | IntPriv(3) | IntTrap

#define IntLength       256

#define IntExtern(x)    extern void int##x(void)
#define IntAddr(x)      ((uint32_t)int##x)
#define IntSet(x, flag) intSetDesc(0x##x, IntAddr(x), flag)

typedef struct int_frame {
    uint32_t intCode;
    uint32_t edi, esi, ebp, esp;
    uint32_t ebx, edx, ecx, eax;
    uint32_t errCode;
    uint32_t eip, cs, eflags;
    uint32_t esp0, ss0;
}int_frame_t;

typedef uint64_t idt_t;

typedef struct idtr {
    uint16_t limit;
    uint32_t address;
} __attribute__((packed)) idtr_t;

IntExtern(03);

void initInterrupt(void);
void lidt(idtr_t *idtr);
void intSetDesc(int index, uint32_t addr, uint16_t flag);

void intHandlerDebug(int_frame_t stack);

#endif
