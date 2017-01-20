.macro segLoadSeg name
    .global segLoad\name
    .type segLoad\name, @function
    segLoad\name :
        movw 4(%esp), %\name
        ret
    .size segLoad\name, . - segLoad\name
.endm

.section .text
.align 4

segLoadSeg DS
segLoadSeg ES
segLoadSeg FS
segLoadSeg GS
segLoadSeg SS

.global segLoadCS
.type segLoadCS, @function
segLoadCS:
    movzwl 4(%esp), %eax
    pushl %eax
    pushl $.L
    lret
.L:
    ret
.size segLoadCS, . - segLoadCS

.global lgdt
.type lgdt, @function
lgdt:
    movl 4(%esp), %eax
    lgdt (%eax)
    ret
.size lgdt, . - lgdt
