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

wrapInterrupt 03, intHandlerDebug
