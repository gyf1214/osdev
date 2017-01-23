.macro wrapInterrupt code, func, err=0
    .global int\code
    .type int\code, @function
    int\code :
.if !\err
        pushl $0
.endif
        pushal
        pushl $0x\code
        call \func
        addl $4, %esp
        popal
        addl $4, %esp
        iret
    .size int\code, . - int\code
.endm

.section .text
.align 4

.global lidt
.type lidt, @function
lidt:
    movl 4(%esp), %eax
    lidt (%eax)
    ret
.size lidt, . - lidt

.global cli
.type cli, @function
cli:
    cli
    ret
.size cli, . - cli

.global sti
.type sti, @function
sti:
    sti
    ret
.size sti, . - sti

.global stihlt
.type stihlt, @function
stihlt:
    sti
    hlt
    ret
.size stihlt, . - stihlt

wrapInterrupt 03, intDebugHandler
wrapInterrupt 40, rtcPeriodicHandler
